#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *waveIn;
    FILE *waveOut;
    if((waveIn = fopen("test.wav", "r")) == NULL){
        perror("open error");
        exit(0);
    }
    if((waveOut = fopen("out.wav", "w")) == NULL){
        perror("open error");
        exit(0);
    }

    char riff[4];
    int fileSize;
    char wave[4];
    char fmt[4];
    int fmtChunkSize;
    int fmtId;
    int channel;
    int fs;
    int dataSpeed;
    int blockSize;
    int bit;
    char dataStr[4];
    int size;

    fread(riff, 1, 4, waveIn);
    fread(&fileSize, 4, 1, waveIn);
    fread(wave, 1, 4, waveIn);
    fread(fmt, 1, 4, waveIn);
    fread(&fmtChunkSize, 4, 1, waveIn);
    fread(&fmtId, 2, 1, waveIn);
    fread(&channel, 2, 1, waveIn);
    fread(&fs, 4, 1, waveIn);
    fread(&dataSpeed, 4, 1, waveIn);
    fread(&blockSize, 2, 1, waveIn);
    fread(&bit, 2, 1, waveIn);
    fread(&dataStr, 1, 4, waveIn);
    fread(&size, 4, 1, waveIn);

    fwrite(riff, 1, 4, waveOut);
    fwrite(&fileSize, 4, 1, waveOut);
    fwrite(wave, 1, 4, waveOut);
    fwrite(fmt, 1, 4, waveOut);
    fwrite(&fmtChunkSize, 4, 1, waveOut);
    fwrite(&fmtId, 2, 1, waveOut);
    fwrite(&channel, 2, 1, waveOut);
    fwrite(&fs, 4, 1, waveOut);
    fwrite(&dataSpeed, 4, 1, waveOut);
    fwrite(&blockSize, 2, 1, waveOut);
    fwrite(&bit, 2, 1, waveOut);
    fwrite(&dataStr, 1, 4, waveOut);
    fwrite(&size, 4, 1, waveOut);

    for(int i = 0; i < size; i++){
        short d;
        fread(&d, 2, 1, waveIn);
        d = (short)(d * 0.5);
        fwrite(&d, 2, 1, waveOut);
    }

    return 0;
}