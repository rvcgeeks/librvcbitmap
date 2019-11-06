/* ___________________________________________________________
 * ____________<<<___#_R_V_C_G_E_E_K_S___>>>__________________
 * CREATED BY #RVCGEEKS @PUNE for more rvchavadekar@gmail.com
 *
 * #RVCGEEKS bitmap library 
 * some functions for pixel modification,image creation,etc...
 * 
*/
//_______________________FUNDAMENTAL BITMAP IMAGE I/O METHODS______________________________

#include"rvcbitmap.h"

Bitmap Bitmap::open(string filename){
    ifstream file(filename.c_str(),ios::in|ios::binary);
    for(int i=0; i<pixels.size(); i++){
        pixels[i].clear();
    }pixels.clear();
    if(file.fail()){
        cout<<filename<<" could not be opened. Does it exist? "
                      <<"Is it already open by another program?\n";
    }else{
        bmpfile_magic magic;
        file.read(reinterpret_cast<char*>(&magic), sizeof(magic));
        if(magic.magic[0]!='B'||magic.magic[1]!='M'){
            cout<<filename<<" is not in proper BMP format.\n";
        }else{
            bmpfile_header header;
            file.read(reinterpret_cast<char*>(&header), sizeof(header));
            bmpfile_dib_info dib_info;
            file.read(reinterpret_cast<char*>(&dib_info), sizeof(dib_info));
            bool flip=true;
            if (dib_info.height < 0){
                flip=false;
                dib_info.height=-dib_info.height;
            }if(dib_info.bits_per_pixel!=24){
                cout<<filename<<" uses "<<dib_info.bits_per_pixel
                    <<"bits per pixel (bit depth). Bitmap only supports 24bit.\n";
                    return *this;
            }if(dib_info.compression){
                cout<<filename<<" is compressed. "
                    <<"Bitmap only supports uncompressed images.\n";
                    return *this;
            }file.seekg(header.bmp_offset);
            for(int row=0;row<dib_info.height;row++){
                vector <Pixel> row_data;
                for(int col=0;col<dib_info.width;col++){
                    int blue=file.get(),green=file.get(),red=file.get();
                    row_data.push_back( Pixel(red, green, blue) );
                }file.seekg(dib_info.width%4,ios::cur);
                if(flip)pixels.insert(pixels.begin(), row_data);
                else pixels.push_back(row_data);
            }file.close();
        }
    }return *this;
}
Bitmap Bitmap::save(string filename, bool mute = false){
    filename+=".bmp";                    //for default .bmp extension to avoid read errors
    ofstream file(filename.c_str(),ios::out|ios::binary);
    if(file.fail()){
        cout<<filename<<" could not be opened for editing. "
            <<"Is it already open by another program or is it read-only?\n";
        return *this;
    }else if(!validate()&&!mute){
        cout<<"Bitmap cannot be saved. It is not a valid image.\n";
        return *this;
    }else{
        bmpfile_magic magic;
        magic.magic[0]='B';magic.magic[1]='M';
        file.write(reinterpret_cast<char*>(&magic),sizeof(magic));
        bmpfile_header header={0};
        header.bmp_offset=sizeof(bmpfile_magic)+sizeof(bmpfile_header)+sizeof(bmpfile_dib_info);
        header.file_size = header.bmp_offset+(pixels.size()*3+pixels[0].size()%4)*pixels.size();
        file.write(reinterpret_cast<char*>(&header),sizeof(header));
        bmpfile_dib_info dib_info={0};
        dib_info.header_size = sizeof(bmpfile_dib_info);
        dib_info.width = pixels[0].size();
        dib_info.height = pixels.size();
        dib_info.num_planes = 1;
        dib_info.bits_per_pixel = 24;
        dib_info.compression = 0;
        dib_info.bmp_byte_size = 0;
        dib_info.hres = 2835;
        dib_info.vres = 2835;
        dib_info.num_colors = 0;
        dib_info.num_important_colors = 0;
        file.write(reinterpret_cast<char*>(&dib_info),sizeof(dib_info));
        for(int row=pixels.size()-1;row>=0;row--){
            const vector <Pixel> & row_data = pixels[row];
            for(int col=0;col<row_data.size();col++){
                const Pixel& pix = row_data[col];
                file.put((uchar_t)(pix.blue));
                file.put((uchar_t)(pix.green));
                file.put((uchar_t)(pix.red));
            }
            for(int i=0;i<row_data.size()%4;i++)  // Rows are padded so that they're always a multiple of 4
                file.put(0);                               // bytes. This line skips the padding at the end of each row.
        }file.close();
    }return *this;
}
