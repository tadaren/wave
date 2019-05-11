#include <stdio.h>
#include <stdlib.h>

int main(){
    FILE *waveIn;
    FILE *waveOut1;
    FILE *waveOut2;
    if((waveIn = fopen("test3.wav", "r")) == NULL){
        perror("open error");
        exit(0);
    }
    if((waveOut1 = fopen("out1.wav", "w")) == NULL){
        perror("open error");
        exit(0);
    }
    if((waveOut2 = fopen("out2.wav", "w")) == NULL){
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

    fwrite(riff, 1, 4, waveOut1);
    fwrite(&fileSize, 4, 1, waveOut1);
    fwrite(wave, 1, 4, waveOut1);
    fwrite(fmt, 1, 4, waveOut1);
    fwrite(&fmtChunkSize, 4, 1, waveOut1);
    fwrite(&fmtId, 2, 1, waveOut1);
    fwrite(&channel, 2, 1, waveOut1);
    fwrite(&fs, 4, 1, waveOut1);
    fwrite(&dataSpeed, 4, 1, waveOut1);
    fwrite(&blockSize, 2, 1, waveOut1);
    fwrite(&bit, 2, 1, waveOut1);
    fwrite(&dataStr, 1, 4, waveOut1);
    fwrite(&size, 4, 1, waveOut1);

    fwrite(riff, 1, 4, waveOut2);
    fwrite(&fileSize, 4, 1, waveOut2);
    fwrite(wave, 1, 4, waveOut2);
    fwrite(fmt, 1, 4, waveOut2);
    fwrite(&fmtChunkSize, 4, 1, waveOut2);
    fwrite(&fmtId, 2, 1, waveOut2);
    fwrite(&channel, 2, 1, waveOut2);
    fwrite(&fs, 4, 1, waveOut2);
    fwrite(&dataSpeed, 4, 1, waveOut2);
    fwrite(&blockSize, 2, 1, waveOut2);
    fwrite(&bit, 2, 1, waveOut2);
    fwrite(&dataStr, 1, 4, waveOut2);
    fwrite(&size, 4, 1, waveOut2);

    short *data = calloc(size, sizeof(short));

    for(int i = 0; i < size; i++){
        short d;
        fread(&d, 2, 1, waveIn);
        d = (short)(d * 0.5);
        fwrite(&d, 2, 1, waveOut1);
        data[i] = d;
    }

    int fc = 50;
    int M = (int)(0.443 * fs / fc);
    M += (M%2+1)%2;
    int M2 = M/2;
    printf("%d\n", M);
    for(int i = 0; i < size; i++){
        int sum = 0;
        for(int j = -M2; j <= M2; j++){
            if(i+j < 0){
                sum += data[0];
            }else if(i+j >= size){
                sum += data[size-1];
            }else{
                sum += data[i+j];
            }
        }
        int ave = sum/M;
        fwrite(&ave, 2, 1, waveOut2);
    }

    return 0;
}