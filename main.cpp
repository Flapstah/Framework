#include "common/stdafx.h"

#include <stdio.h>
#include <stdlib.h>

#include <GL/glfw.h>

#include "common/itime.h"

#include "graphics/display.h"
#include "input/keyboard.h"

#define WINDOW_WIDTH (640)
#define WINDOW_HEIGHT (400)

#define DESIRED_FRAMERATE (10.0)
#define FRAME_INTERVAL (1.0/DESIRED_FRAMERATE)

//==============================================================================
// Path Rendering stuff goes here
//==============================================================================

#define SAMPLES (50)
//#if defined (WIN32)
#define RAND (rand()/(double)RAND_MAX) 
//#else
//#define RAND erand48(Xi)
//#endif // defined (WIN32)

#if defined(WIN32)
#define _USE_MATH_DEFINES
#endif

#include <math.h>   // smallpt, a Path Tracer by Kevin Beason, 2008
//#include <stdlib.h> // Make : g++ -O3 -fopenmp smallpt.cpp -o smallpt
//#include <stdio.h>  //        Remove "-fopenmp" for g++ version < 4.2
struct Vec {        // Usage: time ./smallpt 5000 && xv image.ppm
  double x, y, z;                  // position, also color (r,g,b)
  Vec(double x_=0, double y_=0, double z_=0){ x=x_; y=y_; z=z_; }
  Vec operator+(const Vec &b) const { return Vec(x+b.x,y+b.y,z+b.z); }
  Vec operator-(const Vec &b) const { return Vec(x-b.x,y-b.y,z-b.z); }
  Vec operator*(double b) const { return Vec(x*b,y*b,z*b); }
  Vec mult(const Vec &b) const { return Vec(x*b.x,y*b.y,z*b.z); }
  Vec& norm(){ return *this = *this * (1/sqrt(x*x+y*y+z*z)); }
  double dot(const Vec &b) const { return x*b.x+y*b.y+z*b.z; } // cross:
  Vec operator%(const Vec&b) const {return Vec(y*b.z-z*b.y,z*b.x-x*b.z,x*b.y-y*b.x);}
};
struct Ray { Vec o, d; Ray(Vec o_, Vec d_) : o(o_), d(d_) {} };
enum Refl_t { DIFF, SPEC, REFR };  // material types, used in radiance()
struct Sphere {
  double rad;       // radius
  Vec p, e, c;      // position, emission, color
  Refl_t refl;      // reflection type (DIFFuse, SPECular, REFRactive)
  Sphere(double rad_, Vec p_, Vec e_, Vec c_, Refl_t refl_):
    rad(rad_), p(p_), e(e_), c(c_), refl(refl_) {}
  double intersect(const Ray &r) const { // returns distance, 0 if nohit
    Vec op = p-r.o; // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
    double t, eps=1e-4, b=op.dot(r.d), det=b*b-op.dot(op)+rad*rad;
    if (det<0) return 0; else det=sqrt(det);
    return (t=b-det)>eps ? t : ((t=b+det)>eps ? t : 0);
  }
};
Sphere spheres[] = {//Scene: radius, position, emission, color, material
  Sphere(1e5, Vec( 1e5+1,40.8,81.6), Vec(),Vec(.75,.25,.25),DIFF),//Left
  Sphere(1e5, Vec(-1e5+99,40.8,81.6),Vec(),Vec(.25,.25,.75),DIFF),//Rght
  Sphere(1e5, Vec(50,40.8, 1e5),     Vec(),Vec(.75,.75,.75),DIFF),//Back
  Sphere(1e5, Vec(50,40.8,-1e5+170), Vec(),Vec(),           DIFF),//Frnt
  Sphere(1e5, Vec(50, 1e5, 81.6),    Vec(),Vec(.75,.75,.75),DIFF),//Botm
  Sphere(1e5, Vec(50,-1e5+81.6,81.6),Vec(),Vec(.75,.75,.75),DIFF),//Top
  Sphere(16.5,Vec(27,16.5,47),       Vec(),Vec(1,1,1)*.999, SPEC),//Mirr
  Sphere(16.5,Vec(73,16.5,78),       Vec(),Vec(1,1,1)*.999, REFR),//Glas
  Sphere(600, Vec(50,681.6-.27,81.6),Vec(12,12,12),  Vec(), DIFF) //Lite
};
inline double clamp(double x){ return x<0 ? 0 : x>1 ? 1 : x; }
inline int toInt(double x){ return int(pow(clamp(x),1/2.2)*255+.5); }
inline bool intersect(const Ray &r, double &t, int &id){
  double n=sizeof(spheres)/sizeof(Sphere), d, inf=t=1e20;
  for(int i=int(n);i--;) if((d=spheres[i].intersect(r))&&d<t){t=d;id=i;}
  return t<inf;
}
/*
Vec radiance(const Ray &r, int depth, unsigned short *Xi){
  double t;                               // distance to intersection
  int id=0;                               // id of intersected object
  if (!intersect(r, t, id)) return Vec(); // if miss, return black
  const Sphere &obj = spheres[id];        // the hit object
  Vec x=r.o+r.d*t, n=(x-obj.p).norm(), nl=n.dot(r.d)<0?n:n*-1, f=obj.c;
  double p = f.x>f.y && f.x>f.z ? f.x : f.y>f.z ? f.y : f.z; // max refl
  if (++depth>5) if (RAND<p) f=f*(1/p); else return obj.e; //R.R.
  if (obj.refl == DIFF){                  // Ideal DIFFUSE reflection
    double r1=2*M_PI*RAND, r2=RAND, r2s=sqrt(r2);
    Vec w=nl, u=((fabs(w.x)>.1?Vec(0,1):Vec(1))%w).norm(), v=w%u;
    Vec d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();
    return obj.e + f.mult(radiance(Ray(x,d),depth,Xi));
  } else if (obj.refl == SPEC)            // Ideal SPECULAR reflection
    return obj.e + f.mult(radiance(Ray(x,r.d-n*2*n.dot(r.d)),depth,Xi));
  Ray reflRay(x, r.d-n*2*n.dot(r.d));     // Ideal dielectric REFRACTION
  bool into = n.dot(nl)>0;                // Ray from outside going in?
  double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.d.dot(nl), cos2t;
  if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0)    // Total internal reflection
    return obj.e + f.mult(radiance(reflRay,depth,Xi));
  Vec tdir = (r.d*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))).norm();
  double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir.dot(n));
  double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P);
  return obj.e + f.mult(depth>2 ? (RAND<P ?   // Russian roulette
    radiance(reflRay,depth,Xi)*RP:radiance(Ray(x,tdir),depth,Xi)*TP) :
    radiance(reflRay,depth,Xi)*Re+radiance(Ray(x,tdir),depth,Xi)*Tr);
}
*/
// From forward.cpp
Vec radiance(const Ray &r_, int depth_, unsigned short *Xi){
  double t;                               // distance to intersection
  int id=0;                               // id of intersected object
  Ray r=r_;
  int depth=depth_;
  // L0 = Le0 + f0*(L1)
  //    = Le0 + f0*(Le1 + f1*L2)
  //    = Le0 + f0*(Le1 + f1*(Le2 + f2*(L3))
  //    = Le0 + f0*(Le1 + f1*(Le2 + f2*(Le3 + f3*(L4)))
  //    = ...
  //    = Le0 + f0*Le1 + f0*f1*Le2 + f0*f1*f2*Le3 + f0*f1*f2*f3*Le4 + ...
  // 
  // So:
  // F = 1
  // while (1){
  //   L += F*Lei
  //   F *= fi
  // }
  Vec cl(0,0,0);   // accumulated color
  Vec cf(1,1,1);  // accumulated reflectance
  while (1){
    if (!intersect(r, t, id)) return cl; // if miss, return black
    const Sphere &obj = spheres[id];        // the hit object
    Vec x=r.o+r.d*t, n=(x-obj.p).norm(), nl=n.dot(r.d)<0?n:n*-1, f=obj.c;
    double p = f.x>f.y && f.x>f.z ? f.x : f.y>f.z ? f.y : f.z; // max refl
    cl = cl + cf.mult(obj.e);
    if (++depth>5) if (RAND<p) f=f*(1/p); else return cl; //R.R.
    cf = cf.mult(f);
    if (obj.refl == DIFF){                  // Ideal DIFFUSE reflection
      double r1=2*M_PI*RAND, r2=RAND, r2s=sqrt(r2);
      Vec w=nl, u=((fabs(w.x)>.1?Vec(0,1):Vec(1))%w).norm(), v=w%u;
      Vec d = (u*cos(r1)*r2s + v*sin(r1)*r2s + w*sqrt(1-r2)).norm();
      //return obj.e + f.mult(radiance(Ray(x,d),depth,Xi));
      r = Ray(x,d);
      continue;
    } else if (obj.refl == SPEC){           // Ideal SPECULAR reflection
      //return obj.e + f.mult(radiance(Ray(x,r.d-n*2*n.dot(r.d)),depth,Xi));
      r = Ray(x,r.d-n*2*n.dot(r.d));
      continue;
    }
    Ray reflRay(x, r.d-n*2*n.dot(r.d));     // Ideal dielectric REFRACTION
    bool into = n.dot(nl)>0;                // Ray from outside going in?
    double nc=1, nt=1.5, nnt=into?nc/nt:nt/nc, ddn=r.d.dot(nl), cos2t;
    if ((cos2t=1-nnt*nnt*(1-ddn*ddn))<0){    // Total internal reflection
      //return obj.e + f.mult(radiance(reflRay,depth,Xi));
      r = reflRay;
      continue;
    }
    Vec tdir = (r.d*nnt - n*((into?1:-1)*(ddn*nnt+sqrt(cos2t)))).norm();
    double a=nt-nc, b=nt+nc, R0=a*a/(b*b), c = 1-(into?-ddn:tdir.dot(n));
    double Re=R0+(1-R0)*c*c*c*c*c,Tr=1-Re,P=.25+.5*Re,RP=Re/P,TP=Tr/(1-P);
    // return obj.e + f.mult(erand48(Xi)<P ?
    //                       radiance(reflRay,    depth,Xi)*RP:
    //                       radiance(Ray(x,tdir),depth,Xi)*TP);
    if (RAND<P){
      cf = cf*RP;
      r = reflRay;
    } else {
      cf = cf*TP;
      r = Ray(x,tdir);
    }
    continue;
  }
}

double render(uint32* pScreen, Vec* pColour)
{
  int w=WINDOW_WIDTH, h=WINDOW_HEIGHT, samps = SAMPLES; // # samples
  Ray cam(Vec(50,52,295.6), Vec(0,-0.042612,-1).norm()); // cam pos, dir
  Vec cx=Vec(w*.5135/h), cy=(cx%cam.d).norm()*.5135, r;
	static int y = 0;
	static int x = 0;

	if (y<h)
	{                       // Loop over image rows
		unsigned short Xi[3]={0, 0, y*y*y};
		if (x<w)
		{
			int i = (h-y-1)*w+x;
#pragma omp parallel for schedule(dynamic, 1) private(r)       // OpenMP
      for (int sy=0; sy<2; sy++)     // 2x2 subpixel rows
			{
        for (int sx=0; sx<2; sx++, r=Vec())
				{        // 2x2 subpixel cols
          for (int s=0; s<samps; s++)
					{
            double r1=2*RAND, dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1);
            double r2=2*RAND, dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2);
            Vec d = cx*( ( (sx+.5 + dx)/2 + x)/w - .5) +
                    cy*( ( (sy+.5 + dy)/2 + y)/h - .5) + cam.d;
            r = r + radiance(Ray(cam.o+d*140,d.norm()),0,Xi)*(1./samps);
          } // Camera rays are pushed ^^^^^ forward to start in interior
					pColour[i] = pColour[i] + Vec(clamp(r.x),clamp(r.y),clamp(r.z))*.25;
					pScreen[i] = toInt(pColour[i].x) | (toInt(pColour[i].y)<<8) | (toInt(pColour[i].z)<<16);
        }
			}
			++x;
		}
		else
		{
			x=0;
			++y;
		}
  }

	double pixel=(y*w)+x;
	double total=(w*h);
	return pixel/total;
}

//==============================================================================

void DumpArgs(int argc, char* argv[])
{
	printf("*** Passed %d arguments:\n", argc);
	for (int i = 0; i < argc; ++i)
	{
		printf("[%d] [%s]\n", i, argv[i]);
	}
	printf("*** End argument list\n");
}

//==============================================================================

void DumpVariableSizes(void)
{
	printf("*** Variable sizes\n");
#define PRINT_SIZE(_type_) printf(#_type_ "\t: %u\n", static_cast<uint32>(sizeof(_type_)))
	PRINT_SIZE(int8);
	PRINT_SIZE(int16);
	PRINT_SIZE(int32);
	PRINT_SIZE(int64);
	PRINT_SIZE(uint8);
	PRINT_SIZE(uint16);
	PRINT_SIZE(uint32);
	PRINT_SIZE(uint64);
	PRINT_SIZE(bool);
	PRINT_SIZE(float);
	PRINT_SIZE(double);
#undef PRINT_SIZE
	printf("*** End variable sizes\n");
}

//==============================================================================

int main(int argc, char* argv[])
{
//	IGNORE_PARAMETER(argc);
//	IGNORE_PARAMETER(argv);
	DumpArgs(argc, argv);

	uint32 screen[WINDOW_WIDTH*WINDOW_HEIGHT];
	for (uint32 i = 0; i < WINDOW_WIDTH*WINDOW_HEIGHT; ++i)
	{
		screen[i] = 0x00ff0000;
	}

	// Path tracing colour array
	Vec* pColour = new Vec[WINDOW_WIDTH*WINDOW_HEIGHT];
	memset(pColour, 0, sizeof(Vec)*WINDOW_WIDTH*WINDOW_HEIGHT);

	engine::CDisplay display(WINDOW_WIDTH, WINDOW_HEIGHT, "Framework test");
	engine::CKeyboard::Initialise();

	engine::ITime* pTime = engine::GetTime();

	engine::IRealTimeClock* pRTC = pTime->GetRealTimeClock();
	engine::ITimer* pGC = pTime->GetGameClock();

	double time = 0.0;
	double timeCount = 0.0;
	double frameCount = 0.0;
	double elapsedTime = 0.0;

	bool run = true;
	while (run)
	{
		timeCount += pRTC->Tick();
		time += pGC->Tick();

		if (time >= FRAME_INTERVAL)
		{
			time -= FRAME_INTERVAL;
			++frameCount;
			run = display.Update(&screen);
		}

		run &= !engine::CKeyboard::IsKeyPressed(GLFW_KEY_ESC);

		// Path tracing
		static double done = 0.0;
		if (done < 1.0)
		{
			done = render(screen, pColour);
			elapsedTime += pRTC->GetFrameTime();
		}

		if (timeCount >= 1.0)
		{
			if (done < 1.0)
			{
				uint32 hours = static_cast<uint32>(elapsedTime/3600.0);
				uint32 minutes = static_cast<uint32>((elapsedTime-(hours*3600))/60.0);
				double seconds = elapsedTime-(hours*3600)-(minutes*60);

				printf("\rRendering (%d spp) %6.3f%%, %03d:%02d:%05.2f",SAMPLES*4, 100.0*done, hours, minutes, seconds);
			}
//			else
//			{
//				printf("*** Framerate: frames %.02f time %.02f %.02ffps\n", frameCount, timeCount, frameCount/timeCount);
//			}
			timeCount -= 1.0;
			frameCount = 0.0;
		}
	}

	uint32 hours = static_cast<uint32>(elapsedTime/3600.0);
	uint32 minutes = static_cast<uint32>((elapsedTime-(hours*3600))/60.0);
	double seconds = elapsedTime-(hours*3600)-(minutes*60);
	printf("\rRendering (%d spp) %6.3f%%, %03d:%02d:%05.2f\n",SAMPLES*4, 100.0, hours, minutes, seconds);

	printf("*** Writing image file\n");
  FILE *f = fopen("image.ppm", "w");         // Write image to PPM file.
  fprintf(f, "P3\n%d %d\n%d\n", WINDOW_WIDTH, WINDOW_HEIGHT, 255);
  for (int i=0; i<WINDOW_WIDTH*WINDOW_HEIGHT; i++)
    fprintf(f,"%d %d %d ", toInt(pColour[i].x), toInt(pColour[i].y), toInt(pColour[i].z));

	printf("********\n");
//	DumpVariableSizes();
	printf("All done.\n");

	engine::CKeyboard::Uninitialise();

	delete[] pColour;
	return 0;
}

//==============================================================================

