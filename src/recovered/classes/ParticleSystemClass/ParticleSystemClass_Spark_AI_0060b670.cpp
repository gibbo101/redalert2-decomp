#include "shared/particle_system.hpp"
#include "shared/id_source.hpp"
#include "shared/spot_light.hpp"
#include "shared/options.hpp"
#include "shared/fast_math.hpp"
extern "C" int __cdecl abs(int value);
#pragma intrinsic(abs)
inline double Random_Double(double low,double high)
{
    int number=unknown_id_source_a3d290->Random()(0,0x7ffffffe);
    return (high-low)*(number/2147483646.0)+low;
}
static inline Vector3 Normalize(Vector3 const &vector);
inline Vector3 operator*(float scale,Vector3 const &vector)
{
    return Vector3(scale*vector.X,scale*vector.Y,scale*vector.Z);
}
void ParticleSystemClass::unknown_func_60b670()
{
    if (unknown_dc>0) {
        if (unknown_dc==1 || Random_Double(0.0,1.0)<=Class->SpawnSparkPercentage) {
            int random=unknown_id_source_a3d290->Random();
            int count=Class->ParticleCap/2+abs(random)%(Class->ParticleCap/2);
            ParticleTypeClass *held=ParticleTypes[Class->HoldsWhat];
            Random2Class &generator=unknown_id_source_a3d290->Random();
            int rand_y=generator;
            int rand_x=unknown_id_source_a3d290->Random();
            Vector3 spark;
            float vertical_velocity=(float)(int(generator)%held->ZVelocityRange);
            spark.X=(float)(rand_x%held->XVelocity);
            spark.Y=(float)(rand_y%held->YVelocity);
            spark.Z=vertical_velocity;
            while (count>0) {
                ParticleClass *particle=Spawn_Particle(Position_Coord_004f3f40(),Position_Coord_004f3f40());
                ParticleTypeClass const *type=particle->Class;
                Vector3 &direction=particle->unknown_fc;
                particle->unknown_fc.X=(float)(int(unknown_id_source_a3d290->Random())%type->XVelocity);
                particle->unknown_fc.Y=(float)(int(unknown_id_source_a3d290->Random())%type->YVelocity);
                particle->unknown_fc.Z=(float)(type->MinZVelocity+abs(int(unknown_id_source_a3d290->Random()))%type->ZVelocityRange);
                float speed=direction.Length();
                if (unknown_e5) particle->unknown_fc=spark+particle->unknown_fc;
                else { Vector3 &spawn_direction=(Vector3 &)Class->SpawnDirection;
                    particle->unknown_fc=spawn_direction+direction; }
                particle->unknown_fc=Normalize(particle->unknown_fc);
                particle->unknown_fc=speed*particle->unknown_fc;
                --count;
            }
            if (Options.DetailLevel==2) {
                if (unknown_dc==Class->SparkSpawnFrames && Class->LightSize>0 && !Class->OneFrameLight)
                    new SpotLightClass(Position_Coord_004f3f40(),Class->LightSize);
            }
        }
        --unknown_dc;
        if (unknown_dc<=0) unknown_e4=true;
        double chance=Random_Double(0.0,1.0);
        if (chance<0.3) {
            int radius;
            if(unknown_e0-3<=17) radius=17; else radius=unknown_e0-3;
            unknown_e0=radius;
        } else if (chance<0.6) {
            int radius=unknown_e0+3;
            if (radius>=41) radius=41;
            unknown_e0=radius;
        }
    }
    int index;
    for (index=0;index<Particles.Count();++index) Particles[index]->unknown_func_609c90();
    for (index=Particles.Count()-1;index>=0;--index) {
        ParticleClass *particle=Particles[index];
        if (particle->unknown_121) particle->unknown_slot60();
    }
}
