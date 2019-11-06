//by @rvcgeeks____ @Pune :: L system line fractal using spawning of children :: n-ary tree recursion
#include<rvcbitmap.h>

#define MAXPTS 20
//_______________________________________________________________________________________________________________
                                          //for storing some sample initial points and parameters for different fractals
struct L_system{                          //the respective fractal is (size - 1) ary tree recursive 
      string name;           float complex p[MAXPTS];                                                   int size ,depth;
}seeds[]={
    {"horn_curve"          ,{150 + 200*I, 550 + 420*I, 500 + 200*I, 450 + 420*I, 850 + 200*I}             ,5    ,11    },
    {"koch_curve"          ,{ 50 + 550*I, 350 + 550*I, 500 + 150*I, 650 + 550*I, 950 + 550*I}             ,5    ,7     },
    {"globules"            ,{ 50 + 200*I, 450 + 400*I, 850 + 200*I, 450 + 400*I, 850 + 200*I}             ,5    ,11    },
    {"sierpinski"          ,{ 50 + 750*I, 500 + 750*I, 275 + 360*I, 725 + 360*I, 500 + 750*I, 950 + 750*I},6    ,10    },
    {"depressed_sierpinski",{ 50 + 450*I, 500 + 450*I, 400 + 250*I, 600 + 250*I, 500 + 450*I, 950 + 450*I},6    ,10    },
    {"fern"                ,{480 + 450*I, 460 + 480*I, 500 + 450*I, 700 + 300*I, 730 + 400*I, 720 + 450*I},6    ,7     },
    {"round_round"         ,{ 50 + 600*I, 500 + 600*I, 358 + 541*I, 300 + 400*I, 358 + 258*I, 500 + 200*I ,
                             641 + 258*I, 700 + 400*I, 641 + 541*I, 500 + 600*I, 950 + 600*I}             ,11   ,5     }
};

PixelMatrix playground;
Pixel scheme_arr[]={
    Pixel(0,0,255),    //BLUE
    Pixel(0,255,0),    //GREEN
    Pixel(0,255,255),  //CYAN
    Pixel(255,0,0),    //RED
    Pixel(255,0,255),  //MAGENTA
    Pixel(128,128,0),  //BROWN
    Pixel(200,200,200),//LIGHTGRAY
    Pixel(70,70,70),   //DARKGRAY
    Pixel(128,128,255),//LIGHTBLUE
    Pixel(128,255,128),//LIGHTGREEN
    Pixel(128,255,255),//LIGHTCYAN
    Pixel(255,128,128),//LIGHTRED
    Pixel(255,128,255),//LIGHTMAGENTA
    Pixel(255,255,0),  //YELLOW
    Pixel(255,255,255) //WHITE
};

//______________________________________ MAIN LOGIC FOR PLOTTING L-SYSTEM CURVES ________________________________

void grow(L_system parents){              //go deep only to a reasonable depth
    L_system children = parents;          //new children for vertices     
    if(children.depth--){int n = parents.size;                                                                                                        
        for(int i = 0; n-i-1; i++){
            for(int j = 0; n-j; j++){     //breed children using the formula as discussed in the illustration image and plot each only if that pixel is dark
                children.p[j] = parents.p[i] + (parents.p[i+1] - parents.p[i]) * (parents.p[j] - parents.p[0]) / (parents.p[n-1] - parents.p[0]); 
                int x = creal(children.p[j]) ,y = cimag(children.p[j]);
                if(x >= 0 && x < 1200 &&y >= 0 && y < 800 && playground[y][x] == Pixel(0,0,0))
                    playground[y][x] = scheme_arr[children.depth];
            }grow(children);              //n-1 ary tree recursion .. pass on the children to next generation
        }
    }
}

//____________________________________________________ DRIVER ___________________________________________________
int main(){
    int  n = sizeof(seeds)/sizeof(L_system); //for fullscreen VGA mode
    for(int i = 0;i < n; i++){            //its showtime show all of talent!!!
        playground=PixelMatrix(1200,800);
        grow(seeds[i]);
        Bitmap(1200,800).fromPixelMatrix(playground).save(seeds[i].name,false);
        cout<<"Finished : "<<seeds[i].name<<endl;
    }
    return 0;
}
