#include <string.h>
#include <stdlib.h>
#include "a5.h"
//Q1
int strind(const char *s, char c){
    int i = 0;
    while (s[i] != '\0'){
        if(s[i] == c){
            return i;
        }
        i++;
    };
    return -1;
}
//Q2
char strmaxfreq(const char *s){
    int sLength = strlen(s);
    if (sLength == 0){
        return '\0';
    }
    int occurence = 0;
    char mostFreqC = '\0';
    int charFreq[256] = {0};
    for(int i = 0; i < sLength; i++){
        charFreq[(unsigned char)s[i]]++;
    }
    for(int i = 0; i < sLength; i++){
        if (charFreq[(unsigned char)s[i]] > occurence){
            occurence = charFreq[(unsigned char)s[i]];
            mostFreqC = s[i];
        }
    }
    return mostFreqC;
    
}
//Q3
char *strrepeat(const char *s, size_t n){
    size_t length = strlen(s);
    char *newStr = malloc((length * n) + 1);
    newStr[0] = '\0';
    for(size_t i = 0; i < n; i++){
        strcat(newStr, s);
    }
    return newStr;
}
