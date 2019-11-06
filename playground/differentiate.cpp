/* ___________________________________________________________
 * ____________<<<___#_R_V_C_G_E_E_K_S___>>>__________________
 * CREATED BY #RVCGEEKS @PUNE for more rvchavadekar@gmail.com
 *
 * #RVCGEEKS commandline bitmap display on terminal...
 * before running please set custom terminal font to 6 and 
 * zoom out maximum to get non distorted image...
 * 
 * to change the display area width modify MAX_TERMINAL_WIDTH
 * in lib/bitmap.h:7:28: according to your terminal width in 
 * above font configuration...
 * 
*/
#include<rvcbitmap.h>
int main(int argc,char *argv[]){
  if(argc!=2){
      cout<<"\n   usage:\n      ~$ "<<argv[0]<<" [path]\n"
            "   where [path] points to a 24 bit bitmap image to open in terminal\n\n";
      return 0;
  }Bitmap image;
  image.open(argv[1]);
  image.rvcdisplay();
  image = TraceEdges(image);
  image.save(string("differentiated-")+string(argv[1]),false);
  return 0;
}
