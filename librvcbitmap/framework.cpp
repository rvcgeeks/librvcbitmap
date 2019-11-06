/* ___________________________________________________________
 * ____________<<<___#_R_V_C_G_E_E_K_S___>>>__________________
 * CREATED BY #RVCGEEKS @PUNE for more rvchavadekar@gmail.com
 *
 * #RVCGEEKS bitmap library 
 * some functions for pixel modification,image creation,etc...
 * 
*/

#include"rvcbitmap.h"

bool Pixel::validate(){
    return red>=MIN_RGB&&
           red<=MAX_RGB&&
           green>=MIN_RGB&&
           green<=MAX_RGB&&
           blue>=MIN_RGB&&
           blue<=MAX_RGB;
}
ostream& operator<<(ostream& inject,const Pixel& p){
    inject<<"\033[48;2;"           //ascii escape for rgb colours
          <<p.red<<";"
          <<p.green<<";"
          <<p.blue<<"m  "
          <<"\033[0m";
    return inject;
}
//________________________________________________________________________

PixelMatrix::PixelMatrix(int width,int height){
    for(int row=0;row<height;row++){
        vector<Pixel> row_data;
        for(int col=0;col<width;col++){
            row_data.push_back(Pixel(MIN_RGB,MIN_RGB,MIN_RGB));              //create a black image (black paper) of width X height pixels
        }this->push_back(row_data);
    }
}
PixelMatrix PixelMatrix::rvcdisplay(){
    const int height=this->size(),width=(*this)[0].size();
    for(int row=0;row<height;row+=1+width/MAX_TERMINAL_WIDTH){
        for(int column=0;column<width;column+=1+width/MAX_TERMINAL_WIDTH)
            cout<<(*this)[row][column];
        cout<<endl;
    }cout<<endl;return *this;
}
//________________________________________________________________________

Bitmap::Bitmap(int width,int height){
    pixels=PixelMatrix(width,height);
}
bool Bitmap::validate(){
    const int height=pixels.size();
    if(height==0||pixels[0].size()==0)
        return false;
    const int width=pixels[0].size();
    for(int row=0;row<height;row++){
        if(pixels[row].size()!=width)
            return false;
        for(int column=0; column < width; column++){
            Pixel current = pixels[row][column];
            if(!current.validate()){
                cout<<"Fault @ row = "<<row<<" column = "<<column<<endl
                    <<"Pixel values = { r : "<<current.red<<" , g : "<<current.green<<" , b : "<<current.blue<<" }\n";
                return false;
            }
        }
    }return true;
}
PixelMatrix Bitmap::toPixelMatrix(){
    if(validate()) return pixels;
    else return PixelMatrix();
}
Bitmap Bitmap::fromPixelMatrix(const PixelMatrix& values){
    pixels = values;
    return *this;
}
Bitmap Bitmap::rvcdisplay(){
    return fromPixelMatrix(pixels.rvcdisplay());
}
