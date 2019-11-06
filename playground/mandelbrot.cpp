/* ___________________________________________________________
 * ____________<<<___#_R_V_C_G_E_E_K_S___>>>__________________
 * CREATED BY #RVCGEEKS @PUNE for more rvchavadekar@gmail.com
 * 
 * Create a mandelbrot fractal in bmp format image...
 * using rvcbitmap library
 * 
 */
#include<rvcbitmap.h>
#include<time.h>        //calculate execution time

//____________________COLOR SCHEMES FOR COLOURING__________________________
Pixel colors0[]={       // rainbow theme (suited for Mandelbrot and Julia)
    Pixel(0,255,255),   //cyan
    Pixel(0,0,255),     //blue
    Pixel(255,0,255),   //magenta
    Pixel(0,0,0),       //black
    Pixel(255,0,0),     //red
    Pixel(255,127,0),   //orange
    Pixel(255,255,0),   //yellow
    Pixel(0,255,0)      //green
};
vector<Pixel> scheme0(colors0,colors0+sizeof(colors0)/sizeof(Pixel));   //make a color scheme for blending with iterations

Pixel colors1[]={       // fire theme (suited for Mandelbrot)
    Pixel(0,0,0),       //black
    Pixel(0,0,0),       //black
    Pixel(0,0,0),       //black
    Pixel(0,0,0),       //black
    Pixel(255,0,0),     //red
    Pixel(255,127,0),   //orange
    Pixel(255,255,0),   //yellow
    Pixel(255,255,0),   //yellow
    Pixel(255,255,255)  //white
};
vector<Pixel> scheme1(colors1,colors1+sizeof(colors1)/sizeof(Pixel));

Pixel colors2[]={       // mystic theme (suited for Glynn)
    Pixel(0,255,0),     //green
    Pixel(255,255,255), //white
    Pixel(0,0,0),       //black
    Pixel(0,0,0),       //black
    Pixel(0,0,255),     //blue
    Pixel(255,0,0),     //red
    Pixel(255,255,0),   //yellow
    Pixel(255,0,255)    //magenta
};
vector<Pixel> scheme2(colors2,colors2+sizeof(colors2)/sizeof(Pixel));

void display_scheme(vector<Pixel> v){
    for(vector<Pixel>::iterator it=v.begin();it!=v.end();it++)
        cout<<*it;
    cout<<"repeat";
}

//______________________________MANDELBROT SET________________________________________
PixelMatrix Draw_Mandelbrot(
    int fractal_width,
    int fractal_height,
    uint32_t max_iterations,
    vector<Pixel> scheme,
    float threshold,
    float xs,
    float ys,
    float expn =2.0f,
    float scale=1.0f
){
    PixelMatrix fractal(fractal_width,fractal_height);
    float complex c,z;
    for(uint32_t y=0;y<fractal_height;++y){
        for(uint32_t x=0;x<fractal_width;++x){z = 0;
            c = (1.5 * (2.0 * x / fractal_width  - 1.0 - xs) - 0.5 
                     + (2.0 * y / fractal_height - 1.0 + ys) * I ) / scale;
            for (uint32_t i = 0; i < max_iterations; i++)
                if(cabs(z = cpow(z,expn) + c) > threshold){
                    if(max_iterations!=i){
                        #define log2(x) log(x)/log(2)
                        fractal[y][x]=blender(0.25,log2(1.75+i-log2(log2(cabs(z))))/log2(max_iterations),scheme);
                        #undef  log2          //2 for fire theme
                    }break;
                }
            int p = (x + y*fractal_height)%(fractal_width*fractal_height / 100);
            if(p==1)cout<<float(x + y*fractal_width)/(fractal_width*fractal_height)*100<<" % completed...\n";
        }
    }return fractal;
}

//_________________________________JULIA SET____________________________________________
PixelMatrix Draw_Julia(
    int fractal_width,
    int fractal_height,
    uint32_t max_iterations,
    vector<Pixel> scheme,
    float threshold,
    float xs,
    float ys,
    float expn =2.0f,
    float scale=1.0f
){
    float cr,ci;
    cout<<" \nEnter the initialization to set : Real (-0.1948 for Glynn Set -0.7 for Julia Set) = ";
    cin>>cr;cout<<" Imaginary (0 for Glynn Set and 0.27015 for Julia set) = ";cin>>ci;
    PixelMatrix fractal(fractal_width,fractal_height);
    float complex c = cr + ci*I,z;
    for(uint32_t y=0;y<fractal_height;++y){
        for(uint32_t x=0;x<fractal_width;++x){
            z = (1.5 * (2.0 * x / fractal_width  - 1.0 - xs) 
                     + (2.0 * y / fractal_height - 1.0 - ys) * I ) / scale;
            for (uint32_t i = 0; i < max_iterations; i++)
                if (cabs(z = cpow(z,expn) + c) > threshold){
                    if (max_iterations != i)
                        fractal[y][x]=blender(500,1000.0*i/max_iterations,scheme);
                    break;
                }
            int p = (x + y*fractal_height)%(fractal_width*fractal_height / 100);
            if(p==1)cout<<float(x + y*fractal_width)/(fractal_width*fractal_height)*100<<" % completed...\n";
        }
    }return fractal;
}


//____________________________________DRIVER_____________________________________________
main(){
    int opt;char opt1;
    PixelMatrix (*FractalGenerator)(int,int,uint32_t,vector<Pixel>,float,float,float,float,float);  //funtion pointer to choose fractal to plot
here:cout<<" \nChoose One of the following fractal to plot:\n"
           " 1) Mandelbrot Set\n"
           " 2) Julia Set\n >>>  ";
    cin>>opt;
    if(opt==1)
        FractalGenerator=Draw_Mandelbrot;
    else if(opt==2)
        FractalGenerator=Draw_Julia;
    else goto here;
    int fractal_width,fractal_height;
    cout<<" \nFor "<<(opt==1?"Mandelbrot":"Julia")<<" fractal:\n"
          " \nResolution of output fractal bitmap:\n"
          " (width X height) (eg 4800 3200) = ";
    cin>>fractal_width>>fractal_height;
    float xs,ys,s;
    cout<<" \nCentre at (xs ys)\n"
          " (eg 0 0 for Mandelbrot and Julia and 1.5 0 for Glynn) = ";
    cin>>xs>>ys;
    float thr;
    cout<<" \nEnter the threshold for set:\n"
          " (typically 2 for all) :";
    cin>>thr;
    float ex;
    cout<<" \nEnter the exponent constant for Set:"
          " \n(2 for Mandelbrot and Julia Sets and 1.5 for Glynn set in Julia mode...).. = ";
    cin>>ex;
    cout<<" \nEnter the scale of zooming (1 suggested for mandelbrot and Julia 4.2 suggested for Glynn) = ";
    cin>>s;
    uint32_t max_iterations;
    cout<<" \nMaximum iterations for "<<(opt==1?"Mandelbrot":"Julia")<<" fractal:\n"
          " (eg "<<(opt==1?"1000":"300")<<") = ";
    cin>>max_iterations;
    vector<Pixel> selected_scheme;int sch_opt = 1;  //rainbow theme by default (to avoid case error)
    cout<<" \nPlease select a color scheme to plot iterations:\n 1) ";
    display_scheme(scheme0);
    cout<<" \n 2) ";display_scheme(scheme1);
    cout<<" \n 3) ";display_scheme(scheme2);
    cout<<" \n\n >>>";cin>>sch_opt;
    switch(sch_opt){
        case 1:selected_scheme = scheme0;break;
        case 2:selected_scheme = scheme1;break;
        case 3:selected_scheme = scheme2;
    }string filename;
    cout<<" \nName of bmp file to save: ";cin>>filename;
    
    clock_t t=clock();                     //start clock
    
    Bitmap().fromPixelMatrix(                 //fire up the plotting and all corresponding actions ...
        FractalGenerator(
            fractal_width,
            fractal_height,
            max_iterations,
            selected_scheme,
            thr,xs,ys,ex,s
        )
    ).save(filename, false);
    
    t=clock()-t;                            //stop clock
    
    cout<<"\a Fractal saved to '"<<filename<<".bmp' successfully in "
        <<(long double)t/CLOCKS_PER_SEC<<" seconds successfully!!\n"
          " Plot more fractals?!? [y/n]:";cin>>opt1;
    if(opt1=='y')goto here;
    cout<<"\n  <<<   STAY TUNED !!!   >>>\n";
    return 0;
}
