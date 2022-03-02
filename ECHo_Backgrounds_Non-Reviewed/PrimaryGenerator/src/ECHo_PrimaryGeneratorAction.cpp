#include "../include/ECHo_PrimaryGeneratorAction.hh"
#include "../../DetectorConstruction/include/ECHo_DetectorConst.hh"
#include "../../DetectorConstruction/include/Volume_names.hh"

//#include <G4LogicalVolumeStore.hh>
//#include <G4LogicalVolume.hh>
//#include <G4Box.hh>
//#include <G4RunManager.hh>
#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <G4ParticleDefinition.hh>
#include <G4SystemOfUnits.hh>
//#include <G4UniformRand.hh>
#include <Randomize.hh>

#include <G4IonTable.hh>

ECHo_PrimaryGeneratorAction::ECHo_PrimaryGeneratorAction(
    ECHo_DetectorConstruction *det, G4bool mu, G4bool cont,
    G4int nucz, G4int nuca, G4String name)
    : G4VUserPrimaryGeneratorAction(), fDetector(det),  contamination(cont),
        muon(mu), nucA(nuca), nucZ(nucz){

    SelectVolume(name);
    const G4double delta_x = thickness[0] + thickness[1]; // left + right
    const G4double delta_y = thickness[2] + thickness[3]; // front + back
    const G4double delta_z = thickness[4] + thickness[5]; // top + bottom

    const G4double shift_x = thickness[0] - thickness[1]; // left - right
    const G4double shift_y = thickness[3] - thickness[2]; // back - front
    const G4double shift_z = thickness[5] - thickness[4]; // bottom - top

    const G4double xy = Lx * Ly;
    const G4double xz = Lx * Lz;
    const G4double yz = Ly * Lz;

    length_x = Lx - delta_x;
    length_y = Ly - delta_y;
    length_z = Lz - delta_z;

    shift_x0 = x0 + shift_x;
    shift_x0_min = shift_x0 - 0.5 * length_x - depth;
    shift_x0_max = shift_x0 + 0.5 * length_x + depth;

    shift_y0 = y0 + shift_y;
    shift_y0_min = shift_y0 - 0.5 * length_y - depth;
    shift_y0_max = shift_y0 + 0.5 * length_y + depth;

    shift_z0 = z0 + shift_z;
    shift_z0_min = shift_z0 - 0.5 * length_z - depth;
    shift_z0_max = shift_z0 + 0.5 * length_z + depth;

    G4double surface[6]{0., 0., 0., 0., 0., 0.};
    G4double inner_surface[6]{0., 0., 0., 0., 0., 0.};
    G4double total_area_inner = 0.;

    if (isShielding){
        const G4double diameter_x = Lx - delta_x;
        const G4double diameter_y = Ly - delta_y;
        const G4double diameter_z = Lz - delta_z;

        for (int i = 0; i < 6; i++){
            if (thickness[i]){
                switch ((int) i / 2){
                    case 0:
                        surface[i] = yz;
                        inner_surface[i] = diameter_y * diameter_z;
                        volume[i] = surface[i] * thickness[i];
                        break;
                    case 1:
                        surface[i] = xz;
                        inner_surface[i] = diameter_x * diameter_z;
                        volume[i] = diameter_x * Lz * thickness[i];
                        break;
                    default:
                        surface[i] = xy;
                        inner_surface[i] = diameter_x * diameter_y;
                        volume[i] = inner_surface[i] * thickness[i];
                }
            }
            total_area_inner += inner_surface[i];
            total_volume += volume[i];
        }
        inner_surface00 = inner_surface[0];
        inner_surface01 = inner_surface00 + inner_surface[1];
        inner_surface02 = inner_surface01 + inner_surface[2];
        inner_surface03 = inner_surface02 + inner_surface[3];
        inner_surface04 = inner_surface03 + inner_surface[4];
    } else{
        surface[0]= yz;
        surface[1] = yz;
        surface[2] = xz;
        surface[3] = xz;
        surface[4] = xy;
        if (not isMMC) surface[5] = xy;
        total_volume = xy * Lz;
    }

    for (int i = 0; i < 6; i++) total_area_outer += surface[i];

    // std::cout << total_volume / CLHEP::cm3 << std::endl;
    total_area = total_area_outer + total_area_inner;

    volume01 = volume[0] + volume[1]; // left + right
    volume23 = volume[2] + volume[3]; // front + back
    volume45 = volume[4] + volume[5]; // top + bottom

    surface00 = surface[0];
    surface01 = surface00 + surface[1];
    surface02 = surface01 + surface[2];
    surface03 = surface02 + surface[3];
    surface04 = surface03 + surface[4];

    //std::cout << x0 << " " << y0 << " " << z0 << std::endl;
    //std::cout << volume << std::endl;

    if (muon){
        G4ParticleTable* ParticleTable = G4ParticleTable::GetParticleTable();
        G4ParticleDefinition* Particle = ParticleTable->FindParticle("mu-");
        fParticleGun->SetParticleDefinition(Particle);
    //} else{
    //    G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(nucA, nucZ, 0.);
    //    //std::cout << "here" << std::endl;
    //    fParticleGun->SetParticleDefinition(ion);
    //    fParticleGun->SetParticleCharge(0.);
    }
    fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
    fParticleGun->SetParticleEnergy(0.);
}


static inline G4double GetN(G4ThreeVector p, G4ThreeVector v, G4double r){

    G4double v2 = v.getX() * v.getX() + v.getY() * v.getY() + v.getZ() * v.getZ();
    G4double p2 = p.getX() * p.getX() + p.getY() * p.getY() + p.getZ() * p.getZ();
    G4double pv2 = v.getX() * p.getX() + v.getY() * p.getY() + v.getZ() * p.getZ();

    G4double b = pv2 / v2;
    G4double c = (p2 - r * r) / (2. * v2);

    return -b + std::sqrt(b * b - 2. * c);
}


static inline G4double Fcos2(G4double theta){
    // From 0 to pi /2
    // return (0.5 * (theta + sin(theta) * cos(theta))) / (CLHEP::pi / 4.);
    return (theta + sin(theta) * cos(theta)) / CLHEP::halfpi;
}


static inline G4double GetInverse(
    G4double x, G4double minVal, G4double maxVal, G4double (f)(G4double)){

    G4double high = maxVal;
    G4double low = minVal;
    G4double mid = (high + low) / 2.;
    const G4double gab = 1e-5;

    while ((high - low) > gab){
        if ((f)(mid) == x) return mid;
        if ((f)(mid) < x) low = mid;
        else high = mid;

        mid = (high + low) / 2.;
    }
    return mid;
}


static inline G4double GetEnergy(G4double x, std::vector<G4double> en_di){
    int first = 0;
    int last = en_di.size() - 1;
    int mid = (last + first) / 2;
    while ((last - first) > 1){
        if (en_di[mid] == x) return mid;
        if (en_di[mid] > x) last = mid;
        else first = mid;

        mid = (first + last) / 2;
    }
    return (G4double) mid;
}


void ECHo_PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent){
    G4double rx = G4UniformRand() - 0.5;
    G4double ry = G4UniformRand() - 0.5;
    G4double rz = G4UniformRand() - 0.5;

    G4double x = x0 + Lx * rx;
    G4double y = y0 + Ly * ry;
    G4double z = z0 + Lz * rz;

    G4double random_mult = G4UniformRand();

    if (muon){
        G4double theta = GetInverse(G4UniformRand(), 0., CLHEP::halfpi, Fcos2);
        G4double phi = CLHEP::twopi * random_mult;
        G4double vx = cos(phi) * sin(theta);
        G4double vy = sin(phi) * sin(theta);

        G4double vz = cos(theta);
        if (vz > 0) vz *= -1;

        G4double thisN = GetN(
            G4ThreeVector(x, y, z), G4ThreeVector(-vx, -vy, -vz), 3 * CLHEP::m);


        G4double entry = GetEnergy(G4UniformRand(), fDetector->GetEnDi());
        //G4double xi = entry  + 1.;
        //G4double energy = xi / cos(theta);
        fParticleGun->SetParticleEnergy((entry  + 1.) / cos(theta));
        fParticleGun->SetParticleMomentumDirection(G4ThreeVector(vx, vy, vz));
        x -= thisN * vx;
        y -= thisN * vy;
        z -= thisN * vz;

    } else if (contamination){ // Bulk contamination
        G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(nucA, nucZ, 0.);
        //std::cout << "here" << std::endl;
        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(0.);
        if (isShielding){
            G4double random_volume = G4UniformRand() * total_volume;
            if (random_volume <= volume01){ // If in left or right side
                if (random_volume <= volume[0]) // If left
                    // Move to left/right side: -/+ halfLength
                    // Get random position on layer: thickness * random_mult
                    x = min_x0 + thickness[0] * random_mult;
                else x = max_x0 - thickness[1] * random_mult;
            } else{
                // Resize box and thus origin: shift_x0
                // Choose random position in resized box: length_x * rx
                x = shift_x0 + length_x * rx;
                random_volume -= volume01;
                if (random_volume <= volume23){ // If in front or back side
                    if (random_volume <= volume[3]) // If back
                        // Move to back/front side: -/+ halfLength
                        // Get random position on layer: thickness * random_mult
                        y = min_y0 + thickness[3] * random_mult;
                    else y = max_y0 - thickness[2] * random_mult;
                } else{
                    // Resize box and thus origin: shift_y0
                    // Choose random position in resized box: length_y * ry
                    y = shift_y0 + length_y * ry;
                    random_volume -= volume23;
                    if (random_volume <= volume[5]) // If bottom
                        z = min_z0 + thickness[5] * random_mult;
                    else z = max_z0 - thickness[4] * random_mult;
                }
            }
        } else if (isPCB){
            z = pcb_z + pcb_dz * rz;

            /*
            G4double random_volume = random_mult * pcb_totalA;
            if (random_volume <= pcb_A0){
                x = pcb_x0 + pcb_dx0 * rx;
                y = pcb_dy0 * ry;
                if (G4UniformRand() < 0.5) y -= pcb_y0;
                else y += pcb_y0;
            } else if (random_volume <= pcb_A1){
                x = pcb_x1 + pcb_dx1 * rx;
                y = pcb_y1 + pcb_dy1 * ry;
            } else{
                x = pcb_x2 + pcb_dx2 * rx;
                y = pcb_y2 + pcb_dy2 * ry;
                if (G4UniformRand() < 0.5) x += pcb_dx0 + pcb_dx2;
            }
            */

            x = pcb_xl + pcb_dxl * rx;
            y = pcb_y2 + pcb_dy2 * ry;
        }
    } else{ // Surface contamination
        G4ParticleDefinition *ion = G4IonTable::GetIonTable()->GetIon(nucA, nucZ, 0.);
        //std::cout << "here" << std::endl;
        fParticleGun->SetParticleDefinition(ion);
        fParticleGun->SetParticleCharge(0.);
        if (isPCB){
            if (G4UniformRand() < 0.5) z = pcb_z + pcb_dz * 0.5;
            else z = pcb_z - pcb_dz * 0.5;
            G4double random_volume = random_mult * pcb_totalA;
            if (random_volume <= pcb_A0){
                x = pcb_x0 + pcb_dx0 * rx;
                y = pcb_dy0 * ry;
                if (G4UniformRand() < 0.5) y -= pcb_y0;
                else y += pcb_y0;
            } else if (random_volume <= pcb_A1){
                x = pcb_x1 + pcb_dx1 * rx;
                y = pcb_y1 + pcb_dy1 * ry;
            } else{
                x = pcb_x2 + pcb_dx2 * rx;
                y = pcb_y2 + pcb_dy2 * ry;
                if (G4UniformRand() < 0.5) x += pcb_dx0 + pcb_dx2;
            }
        } else{
            G4double random_area = random_mult * total_area;
            if (random_area <= total_area_outer){ // If at outer surface
                if (random_area <= surface00) x = min_x;
                else if (random_area <= surface01) x = max_x;
                else if (random_area <= surface02) y = max_y;
                else if (random_area <= surface03) y = min_y;
                else if (random_area <= surface04) z = max_z;
                else z = min_z;
            } else{ // At inner surface
                random_area -= total_area_outer;

                x = shift_x0 + length_x * rx;
                y = shift_y0 + length_y * ry;
                z = shift_z0 + length_z * rz;

                if (random_area <= inner_surface00) x = shift_x0_min;
                else if (random_area <= inner_surface01) x = shift_x0_max;
                else if (random_area <= inner_surface02) y = shift_y0_max;
                else if (random_area <= inner_surface03) y = shift_y0_min;
                else if (random_area <= inner_surface04) z = shift_z0_max;
                else z = shift_z0_min;
            }
        }
    }
    fParticleGun->SetParticlePosition(G4ThreeVector(x, y, z));
    fParticleGun->GeneratePrimaryVertex(anEvent);
}


static G4ThreeVector GetPositionMMC(const G4String name)
{
    const char num = name[0];
    G4ThreeVector a;
    G4ThreeVector b;
    G4ThreeVector out;
    switch (num)
    {
        case '0':
            out = position_AbsorberInMMC;
            break;
        case '1':
            a = GetPositionMMC(name_Absorber);
            b = position_SilverInAbsorber;
            out = G4ThreeVector(
                a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
            break;
        case '2':
            a = GetPositionMMC(name_Silver);
            b = position_HolmiumInSilver;
            out = G4ThreeVector(
                a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
            break;
        case '3':
            out = position_SensorInMMC;
            break;
        default:
            out = G4ThreeVector(0., 0., 0.);
    }
    return out;
}


static G4ThreeVector GetPosition1K(const G4String name)
{
    ECHo_DetectorConst& detVec = get_DetectorConst();
    detVec.setVectors();

    const char num = name[0];
    G4ThreeVector a;
    G4ThreeVector b;
    G4double x;
    G4double y;
    G4double z;
    int digit;
    G4ThreeVector out;
    switch (num)
    {
        case '5':
            out = position_WaferIn1K;
            break;
        case '6':
            a = position_WaferIn1K;
            b = position_sWaferInWafer;
            out = G4ThreeVector(
                a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
            break;
        case '7':
            out = position_BathIn1K;
            break;
        case '8':
            //const int digit_0 = name[name.size() - 1] - '0';
            digit = name[name.size() - 1] - '0';
            if (name[name.size() - 2] != '_')
                    digit = (name[name.size() - 2] - '0') * 10 + digit;
            if ((digit < 17) and (digit >= 0))
            {
                x = detVec.vector_position_x_BathIn1K[digit];
                y = detVec.vector_position_y_BathIn1K[digit];
                z = detVec.vector_position_z_BathIn1K[digit];
                out = G4ThreeVector(x, y, z);
            }
            else out = G4ThreeVector(0., 0., 0.);
            break;
        case '9':
            out = position_SourceIn1K;
            break;
        case 'a':
            out = G4ThreeVector(0., 0., 0.);
            break;
        default:
            //const int digit = name[name.size() - 1] - '0';
            //const int row = name[name.size() - 2] - 'A';
            if ((name[name.size() - 1] - '0' < 0) or
                (name[name.size() - 1] - '0' > 8) or
                (name[name.size() - 2] - 'A' < 0) or
                (name[name.size() - 2] - 'A' > 7))
            {
                out = G4ThreeVector(0., 0., 0.);
            }
            else
            {
                const int pos = (name[name.size() - 1] - '0') * 8 + \
                    name[name.size() - 2] - 'A';
                //std::cout << name[name.size() - 1] << std::endl;
                //std::cout << (name[name.size() - 1] - '0') * 8 << std::endl;
                //std::cout << name[name.size() - 2] << std::endl;
                //std::cout << name[name.size() - 2] - 'A' << std::endl;
                //std::cout << pos << std::endl;
                x = detVec.vector_position_x_MMCIn1K[pos];
                y = detVec.vector_position_y_MMCIn1K[pos];
                z = detVec.vector_position_z_MMCIn1K[pos];

                a = GetPositionMMC(name);
                out = G4ThreeVector(a.getX() + x, a.getY() + y, a.getZ() + z);
            }
            //std::cout << a.getX() / CLHEP::cm << " " <<  a.getY() / CLHEP::cm << " " << a.getZ() / CLHEP::cm << std::endl;
            //std::cout << x / CLHEP::cm << " " << y / CLHEP::cm << " " << z / CLHEP::cm << std::endl;
    }
    return out;
}


static G4ThreeVector GetPositionCopper(const G4String name)
{
    const char num = name[0];
    G4ThreeVector a;
    G4ThreeVector b;
    switch (num)
    {
        case 'b':
            a = position_B0InInnerS;
            b = G4ThreeVector(0., 0., 0.);
            break;
        case 'c':
            a = GetPositionCopper(name_CopperA);
            b = position_Copper500InCB0;
            break;
        case 'd':
            a = GetPositionCopper(name_Copper500);
            b = position_Copper50InCopper500;
            break;
        case 'e':
            a = GetPositionCopper(name_Copper50);
            b = position_Copper5InCopper50;
            break;
        default:
            a = G4ThreeVector(0., 0., 0.);
            b = G4ThreeVector(0., 0., 0.);
    }
    return G4ThreeVector(
        a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
}


static G4ThreeVector GetPositionInnerS(const G4String name)
{
    const char num = name[0];
    char digit;
    G4ThreeVector out;
    switch (num)
    {
        case 'b':
            out = GetPositionCopper(name);
            break;
        case 'c':
            out = GetPositionCopper(name);
            break;
        case 'd':
            out = GetPositionCopper(name);
            break;
        case 'e':
            out = GetPositionCopper(name);
            break;
        case 'g':
            out = G4ThreeVector(0., 0., 0.);
            break;
        case 'm':
            digit = name[name.size() - 1];
            switch (digit)
            {
                case 'p':
                    out = position_CB0TopInInnerS;
                    break;
                case 'm':
                    out = position_CB0BottomInInnerS;
                    break;
                case '1':
                    out = position_CB1InInnerS;
                    break;
                case '2':
                    out = position_CB2InInnerS;
                    break;
                case '3':
                    out = position_CB3InInnerS;
                    break;
                default:
                    out = G4ThreeVector(0., 0., 0.);
            }
            break;
        case 'n':
            digit = name[name.size() - 1];
            switch (digit)
            {
                case '0':
                    out = position_SQTopLInInnerS;
                    break;
                case '1':
                    out = position_SQTopRInInnerS;
                    break;
                case '2':
                    out = position_SQBottomLInInnerS;
                    break;
                case '3':
                    out = position_SQBottomRInInnerS;
                    break;
                default:
                    out = G4ThreeVector(0., 0., 0.);
            }
            break;
        default:
            const G4ThreeVector a = GetPosition1K(name);
            const G4ThreeVector b = position_1KInInnerS;
            out = G4ThreeVector(
                a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
            //std::cout << a.getX() / CLHEP::cm << " " <<  a.getY() / CLHEP::cm << " " << a.getZ() / CLHEP::cm << std::endl;
            //std::cout << b.getX() / CLHEP::cm << " " <<  b.getY() / CLHEP::cm << " " << b.getZ() / CLHEP::cm << std::endl;
    }
    return out;
}


G4ThreeVector GetPositionS5(const G4String name)
{
    const char num = name[0];
    G4ThreeVector out;
    switch (num)
    {
        case 'k':
            out = G4ThreeVector(0., 0., 0.);
            break;
        default:
            const G4ThreeVector a = GetPositionInnerS(name);
            const G4ThreeVector b = position_InnerSInS5;
            out = G4ThreeVector(
                a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
            //std::cout << a.getX() / CLHEP::cm << " " <<  a.getY() / CLHEP::cm << " " << a.getZ() / CLHEP::cm << std::endl;
            //std::cout << b.getX() / CLHEP::cm << " " <<  b.getY() / CLHEP::cm << " " << b.getZ() / CLHEP::cm << std::endl;
    }
    return out;
}


G4ThreeVector GetPositionS50(const G4String name)
{
    const char num = name[0];
    G4ThreeVector out;
    switch (num)
    {
        case 'j':
            out = G4ThreeVector(0., 0., 0.);
            break;
        default:
            const G4ThreeVector a = GetPositionS5(name);
            const G4ThreeVector b = position_S5InS50;
            out = G4ThreeVector(
                a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
            //std::cout << a.getX() / CLHEP::cm << " " <<  a.getY() / CLHEP::cm << " " << a.getZ() / CLHEP::cm << std::endl;
            //std::cout << b.getX() / CLHEP::cm << " " <<  b.getY() / CLHEP::cm << " " << b.getZ() / CLHEP::cm << std::endl;
    }
    return out;
}


G4ThreeVector GetPositionS500(const G4String name)
{
    const char num = name[0];
    G4ThreeVector out;
    switch (num)
    {
        case 'i':
            out = G4ThreeVector(0., 0., 0.);
            break;
        default:
            const G4ThreeVector a = GetPositionS50(name);
            const G4ThreeVector b = position_S50InS500;
            out = G4ThreeVector(
                a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
            //std::cout << a.getX() / CLHEP::cm << " " <<  a.getY() / CLHEP::cm << " " << a.getZ() / CLHEP::cm << std::endl;
            //std::cout << b.getX() / CLHEP::cm << " " <<  b.getY() / CLHEP::cm << " " << b.getZ() / CLHEP::cm << std::endl;
    }
    return out;
}


G4ThreeVector GetPositionShielding(const G4String name)
{
    const char num = name[0];
    G4ThreeVector out;
    switch (num)
    {
        case 'h':
            out = G4ThreeVector(0., 0., 0.);
            break;
        default:
            const G4ThreeVector a = GetPositionS500(name);
            const G4ThreeVector b = position_S500InShielding;
            out = G4ThreeVector(
                a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
            //std::cout << a.getX() / CLHEP::cm << " " <<  a.getY() / CLHEP::cm << " " << a.getZ() / CLHEP::cm << std::endl;
            //std::cout << b.getX() / CLHEP::cm << " " <<  b.getY() / CLHEP::cm << " " << b.getZ() / CLHEP::cm << std::endl;
    }
    return out;
}


G4ThreeVector GetPositionBox(const G4String name)
{
    ECHo_DetectorConst& detVec = get_DetectorConst();
    detVec.setVectors();

    const char num = name[0];
    G4ThreeVector out;
    switch (num)
    {
        case 'f':
            out = position_B1InBox;
            break;
        case 'l':
            //const int digit = name[name.size() - 1] - '0';
            if ((name[name.size() - 1] - '0' < 9) and (name[name.size() - 1] - '0' >= 0))
            {
                out = G4ThreeVector(
                    detVec.vector_position_x_PlugInBox[name[name.size() - 1] - '0'],
                    detVec.vector_position_y_PlugInBox[name[name.size() - 1] - '0'],
                    detVec.vector_position_z_PlugInBox[name[name.size() - 1] - '0']);
            }
            else out = G4ThreeVector(0., 0., 0.);
            break;
        case 'm':
            if (name[name.size() - 1] == '4'){
                out = position_CB4InBox;
                break;
            } else{
                const G4ThreeVector a = GetPositionShielding(name);
                const G4ThreeVector b = position_ShieldingInBox;
                out = G4ThreeVector(
                a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
                break;
            }
        case 'o':
            out = G4ThreeVector(0., 0., 0.);
            break;
        default:
            const G4ThreeVector a = GetPositionShielding(name);
            const G4ThreeVector b = position_ShieldingInBox;
            out = G4ThreeVector(
                a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
            //std::cout << a.getX() / CLHEP::cm << " " <<  a.getY() / CLHEP::cm << " " << a.getZ() / CLHEP::cm << std::endl;
            //std::cout << b.getX() / CLHEP::cm << " " <<  b.getY() / CLHEP::cm << " " << b.getZ() / CLHEP::cm << std::endl;
    }
    return out;
}


G4ThreeVector GetPositionSetUp(const G4String name)
{
    ECHo_DetectorConst& detVec = get_DetectorConst();
    detVec.setVectors();

    const char num = name[0];
    G4ThreeVector out;
    switch (num)
    {
        case 'p':
            // const int digit = name[name.size() - 1] - '0';
            // const int row = name[name.size() - 2] - '0';
            if ((name[name.size() - 1] - '0' < 0) or
                (name[name.size() - 2] - '0' < 0) or
                (name[name.size() - 1] - '0' > 3) or
                    (name[name.size() - 2] - '0' > 5)) out = G4ThreeVector(0., 0., 0.);
            else
            {
                switch (name[name.size() - 2] - '0')
                {
                    case 0:
                        out = G4ThreeVector(
                            detVec.vector_position_x_FrPanelInSetUp[name[name.size() - 1] - '0'],
                            detVec.vector_position_y_FrPanelInSetUp[name[name.size() - 1] - '0'],
                            detVec.vector_position_z_FrPanelInSetUp[name[name.size() - 1] - '0']);
                        break;
                    case 1:
                        out = G4ThreeVector(
                            detVec.vector_position_x_BaPanelInSetUp[name[name.size() - 1] - '0'],
                            detVec.vector_position_y_BaPanelInSetUp[name[name.size() - 1] - '0'],
                            detVec.vector_position_z_BaPanelInSetUp[name[name.size() - 1] - '0']);
                        break;
                    case 2:
                        out = G4ThreeVector(
                            detVec.vector_position_x_LePanelInSetUp[name[name.size() - 1] - '0'],
                            detVec.vector_position_y_LePanelInSetUp[name[name.size() - 1] - '0'],
                            detVec.vector_position_z_LePanelInSetUp[name[name.size() - 1] - '0']);
                        break;
                    case 3:
                        out = G4ThreeVector(
                            detVec.vector_position_x_RiPanelInSetUp[name[name.size() - 1] - '0'],
                            detVec.vector_position_y_RiPanelInSetUp[name[name.size() - 1] - '0'],
                            detVec.vector_position_z_RiPanelInSetUp[name[name.size() - 1] - '0']);
                        break;
                    case 4:
                        out = G4ThreeVector(
                            detVec.vector_position_x_ToPanelInSetUp[name[name.size() - 1] - '0'],
                            detVec.vector_position_y_ToPanelInSetUp[name[name.size() - 1] - '0'],
                            detVec.vector_position_z_ToPanelInSetUp[name[name.size() - 1] - '0']);
                        break;
                    case 5:
                        out = G4ThreeVector(
                            detVec.vector_position_x_BoPanelInSetUp[name[name.size() - 1] - '0'],
                            detVec.vector_position_y_BoPanelInSetUp[name[name.size() - 1] - '0'],
                            detVec.vector_position_z_BoPanelInSetUp[name[name.size() - 1] - '0']);
                        break;
                    default:
                        out = G4ThreeVector(0., 0., 0.);
                }
            }
            break;
        case 'q':
            out = G4ThreeVector(0., 0., 0.);
            break;
        default:
            G4ThreeVector a = GetPositionBox(name);
            G4ThreeVector b = position_BoxInVeto;
            out = G4ThreeVector(
                a.getX() + b.getX(), a.getY() + b.getY(), a.getZ() + b.getZ());
            //std::cout << a.getX() / CLHEP::cm << " " <<  a.getY() / CLHEP::cm << " " << a.getZ() / CLHEP::cm << std::endl;
            //std::cout << b.getX() / CLHEP::cm << " " <<  b.getY() / CLHEP::cm << " " << b.getZ() / CLHEP::cm << std::endl;
    }
    return out;
}


G4ThreeVector ECHo_PrimaryGeneratorAction::GetHalfLength(const G4String name){
    const char num = name[0];
    isMMC = false;
    G4ThreeVector out;
    switch (num)
    {
        case '0':
            isMMC = true;
            out = G4ThreeVector(
                x_half_Absorber, y_half_Absorber, z_half_Absorber);
            break;
        case '1':
            isMMC = true;
            out = G4ThreeVector(x_half_Silver, y_half_Silver, z_half_Silver);
            break;
        case '2':
            isMMC = true;
            out = G4ThreeVector(
                x_half_Holmium, y_half_Holmium, z_half_Holmium);
            break;
        case '3':
            isMMC = true;
            out = G4ThreeVector(x_half_Sensor, y_half_Sensor, z_half_Sensor);
            break;
        case '4':
            isMMC = true;
            out = G4ThreeVector(x_half_MMC, y_half_MMC, z_half_MMC);
            break;
        case '5':
            out = G4ThreeVector(x_half_Wafer, y_half_Wafer, z_half_Wafer);
            break;
        case '6':
            out = G4ThreeVector(x_half_sWafer, y_half_sWafer, z_half_sWafer);
            break;
        case '7':
            out = G4ThreeVector(x_half_Bath, y_half_Bath, z_half_Bath);
            break;
        case '8':
            out = G4ThreeVector(x_half_bath, y_half_bath, z_half_bath);
            break;
        case '9':
            out = G4ThreeVector(x_half_Source, y_half_Source, z_half_Source);
            break;
        case 'a':
            out = G4ThreeVector(x_half_1K, y_half_1K, z_half_1K);
            break;
        case 'b':
            out = G4ThreeVector(
                x_half_Copper_B0, y_half_Copper_B0, z_half_Copper_B0);
            break;
        case 'c':
            out = G4ThreeVector(
                x_half_Copper500, y_half_Copper500, z_half_Copper500);
            break;
        case 'd':
            out = G4ThreeVector(
                x_half_Copper50, y_half_Copper50, z_half_Copper50);
            break;
        case 'e':
            out = G4ThreeVector(
                x_half_Copper5, y_half_Copper5, z_half_Copper5);
            break;
        case 'f':
            out = G4ThreeVector(
                x_half_Copper_B1, y_half_Copper_B1, z_half_Copper_B1);
            break;
        case 'g':
            out = G4ThreeVector(x_half_InnerS, y_half_InnerS, z_half_InnerS);
            break;
        case 'h':
            out = G4ThreeVector(
                x_half_Shielding, y_half_Shielding, z_half_Shielding);
            isShielding = true;
            thickness[0] = thickness_Shielding_left;    // left
            thickness[2] = thickness_Shielding_left;    // front
            thickness[3] = thickness_Shielding_left;    // back
            thickness[4] = thickness_Shielding_top;     // top
            thickness[5] = thickness_Shielding_top;     // bottom
            break;
        case 'i':
            out = G4ThreeVector(x_half_S500, y_half_S500, z_half_S500);
            isShielding = true;
            thickness[0] = thickness_S500;
            thickness[2] = thickness_S500;
            thickness[3] = thickness_S500;
            thickness[4] = thickness_S500;
            thickness[5] = thickness_S500;
            break;
        case 'j':
            out = G4ThreeVector(x_half_S50, y_half_S50, z_half_S50);
            isShielding = true;
            thickness[0] = thickness_S50;
            thickness[2] = thickness_S50;
            thickness[3] = thickness_S50;
            thickness[4] = thickness_S50;
            thickness[5] = thickness_S50;
            break;
        case 'k':
            out = G4ThreeVector(x_half_S5, y_half_S5, z_half_S5);
            isShielding = true;
            thickness[0] = thickness_S5;
            thickness[2] = thickness_S5;
            thickness[3] = thickness_S5;
            thickness[4] = thickness_S5;
            thickness[5] = thickness_S5;
            break;
        case 'l':
            out = G4ThreeVector(x_half_Plug, y_half_Plug, z_half_Plug);
            break;
        case 'm':
            //char dig = name[name.size() - 1];
            switch (name[name.size() - 1])
            {
                case 'p':
                    out = G4ThreeVector(x_half_CB0, y_half_CB0, z_half_CB0);
                    break;
                case 'm':
                    out = G4ThreeVector(x_half_CB0, y_half_CB0, z_half_CB0);
                    break;
                case '1':
                    out = G4ThreeVector(x_half_CB1, y_half_CB1, z_half_CB1);
                    break;
                case '2':
                    out = G4ThreeVector(x_half_CB2, y_half_CB2, z_half_CB2);
                    break;
                case '3':
                    out = G4ThreeVector(x_half_CB3, y_half_CB3, z_half_CB3);
                    break;
                case '4':
                    out = G4ThreeVector(x_half_CB4, y_half_CB4, z_half_CB4);
                    break;
                default:
                    out = G4ThreeVector(0., 0., 0.);
            }
            break;
        case 'n':
            out = G4ThreeVector(x_half_SQUID, y_half_SQUID, z_half_SQUID);
            break;
        case 'o':
            out = G4ThreeVector(x_half_Box, y_half_Box, z_half_Box);
            break;
        case 'p':
            //int row = name[name.size() - 2] - '0';
            switch (name[name.size() - 2] - '0')
            {
                case 0:
                    out = G4ThreeVector(
                        x_half_Panel_front_back, y_half_Panel_front_back,
                        z_half_Panel_front_back);
                    break;
                case 1:
                    out = G4ThreeVector(
                        x_half_Panel_front_back, y_half_Panel_front_back,
                        z_half_Panel_front_back);
                    break;
                case 2:
                    out = G4ThreeVector(
                        x_half_Panel_left_right, y_half_Panel_left_right,
                        z_half_Panel_left_right);
                    break;
                case 3:
                    out = G4ThreeVector(
                        x_half_Panel_left_right, y_half_Panel_left_right,
                        z_half_Panel_left_right);
                    break;
                case 4:
                    out = G4ThreeVector(
                        x_half_Panel_top, y_half_Panel_top, z_half_Panel_top);
                    break;
                case 5:
                    out = G4ThreeVector(
                        x_half_Panel_bottom, y_half_Panel_bottom,
                        z_half_Panel_bottom);
                    break;
                default:
                    out = G4ThreeVector(0., 0., 0.);
            }
            break;
        case 'q':
            out = G4ThreeVector(
                x_half_Active_V, y_half_Active_V, z_half_Active_V);
            break;
        default:
            out = G4ThreeVector(0., 0., 0.);
    }
    return out;
}


void ECHo_PrimaryGeneratorAction::SelectVolume(G4String vol)
{
    G4ThreeVector position;
    G4ThreeVector halfLength;
    if (vol.contains("PCB")){
        isPCB = true;
        G4String name = "m_CB_0_Top";
        position = GetPositionSetUp(name);
        halfLength = GetHalfLength(name);

        pcb_A0 = 2. * halfLength.getX() * halfLength.getY();
        pcb_x0 = position.getX();
        pcb_dx0 = 2. * halfLength.getX();
        pcb_y0 = position.getY();
        pcb_dy0 = 2. * halfLength.getY();
        pcb_z = position.getZ();
        pcb_dz = 2. * halfLength.getZ();
        pcb_totalA += pcb_A0;

        name = "m_CB_1";
        position = GetPositionSetUp(name);
        halfLength = GetHalfLength(name);
        pcb_A1 = halfLength.getX() * halfLength.getY() + pcb_A0;
        pcb_x1 = position.getX();
        pcb_dx1 = 2. * halfLength.getX();
        pcb_y1 = position.getY();
        pcb_dy1 = 2. * halfLength.getY();
        pcb_totalA +=  halfLength.getX() * halfLength.getY();

        name = "m_CB_2";
        position = GetPositionSetUp(name);
        halfLength = GetHalfLength(name);
        pcb_x2 = position.getX();
        pcb_dx2 = 2. * halfLength.getX();
        pcb_y2 = position.getY();
        pcb_dy2 = 2. * halfLength.getY();
        pcb_totalA +=  2. * halfLength.getX() * halfLength.getY();

        name = "m_CB_3";
        position = GetPositionSetUp(name);
        halfLength = GetHalfLength(name);
        pcb_xl = position.getX() + pcb_dx2;
        pcb_dxl = 2. * halfLength.getX() - pcb_dx2;


        name = "b_Copper_A";
        position = GetPositionSetUp(name);
        halfLength = GetHalfLength(name);
    } else {
        halfLength = GetHalfLength(vol);
        position = GetPositionSetUp(vol);
    }

    x0 = position.getX();
    y0 = position.getY();
    z0 = position.getZ();

    Lx = 2. * halfLength.getX();
    Ly = 2. * halfLength.getY();
    Lz = 2. * halfLength.getZ();

    min_x0 = x0 - halfLength.getX();
    max_x0 = x0 + halfLength.getX();
    min_x = min_x0 + depth;
    max_x = max_x0 - depth;

    min_y0 = y0 - halfLength.getY();
    max_y0 = y0 + halfLength.getY();
    min_y = min_y0 + depth;
    max_y = max_y0 - depth;

    min_z0 = z0 - halfLength.getZ();
    max_z0 = z0 + halfLength.getZ();
    min_z = min_z0 + depth;
    max_z = max_z0 - depth;
}

