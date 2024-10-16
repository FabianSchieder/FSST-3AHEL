#ifndef FSST_3AHEL_FUNCTIONS_H
#define FSST_3AHEL_FUNCTIONS_H

typedef struct
{
    char* name;
    char* brand;
    char* model;
    float consumption;
    char* driveType;
    int power;

    struct TypeCertificate* previous;
    struct TypeCertificate* next;
}TpyeCertificate;


#endif //FSST_3AHEL_FUNCTIONS_H
