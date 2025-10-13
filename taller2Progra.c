#include <stdio.h>

#define ESTUDIANTES 5
#define ASIGNATURAS 3

int main() {
    float calificaciones[ESTUDIANTES][ASIGNATURAS];
    float promedioEstudiante[ESTUDIANTES];
    float promedioAsignatura[ASIGNATURAS];
    float maxEstudiante[ESTUDIANTES], minEstudiante[ESTUDIANTES];
    float maxAsignatura[ASIGNATURAS], minAsignatura[ASIGNATURAS];
    int aprobados[ASIGNATURAS] = {0};
    int reprobados[ASIGNATURAS] = {0};
    int i, j;

    printf(" INGRESO DE CALIFICACIONES \n");
    for (i = 0; i < ESTUDIANTES; i++) {
        printf("\nEstudiante %d:\n", i + 1);
        for (j = 0; j < ASIGNATURAS; j++) {
            do {
                printf("  Ingrese nota de la asignatura %d (0 - 10): ", j + 1);
                
                if (scanf("%f", &calificaciones[i][j]) != 1) {
                    printf("  Error: Debe ingresar un valor numerico.\n");
                    while (getchar() != '\n');
                    calificaciones[i][j] = -1; 
                } 
                else if (calificaciones[i][j] < 0 || calificaciones[i][j] > 10) {
                    printf("  Error: La calificacion debe estar entre 0 y 10.\n");
                }

            } while (calificaciones[i][j] < 0 || calificaciones[i][j] > 10);
        }
    }

    for (i = 0; i < ESTUDIANTES; i++) {
        float suma = 0;
        maxEstudiante[i] = calificaciones[i][0];
        minEstudiante[i] = calificaciones[i][0];
        for (j = 0; j < ASIGNATURAS; j++) {
            suma += calificaciones[i][j];
            if (calificaciones[i][j] > maxEstudiante[i]) {
                maxEstudiante[i] = calificaciones[i][j];
            }
            if (calificaciones[i][j] < minEstudiante[i]) {
                minEstudiante[i] = calificaciones[i][j];
            }
        }
        promedioEstudiante[i] = suma / ASIGNATURAS;
    }

    for (j = 0; j < ASIGNATURAS; j++) {
        float suma = 0;
        maxAsignatura[j] = calificaciones[0][j];
        minAsignatura[j] = calificaciones[0][j];
        for (i = 0; i < ESTUDIANTES; i++) {
            suma += calificaciones[i][j];
            if (calificaciones[i][j] >= 6) {
                aprobados[j]++;
            } else {
                reprobados[j]++;
            }
            if (calificaciones[i][j] > maxAsignatura[j]) {
                maxAsignatura[j] = calificaciones[i][j];
            }
            if (calificaciones[i][j] < minAsignatura[j]) {
                minAsignatura[j] = calificaciones[i][j];
            }
        }
        promedioAsignatura[j] = suma / ESTUDIANTES;
    }

    printf("\n\nRESULTADOS FINALES \n");
    printf("\n Estadisticas por Estudiante \n");
    for (i = 0; i < ESTUDIANTES; i++) {
        printf("Estudiante %d -> Promedio: %.2f | Maxima: %.2f | Minima: %.2f\n",
               i + 1, promedioEstudiante[i], maxEstudiante[i], minEstudiante[i]);
    }

    printf("\n Estadisticas por Asignatura \n");
    for (j = 0; j < ASIGNATURAS; j++) {
        printf("Asignatura %d -> Promedio: %.2f | Maxima: %.2f | Minima: %.2f\n",
               j + 1, promedioAsignatura[j], maxAsignatura[j], minAsignatura[j]);
        printf("               Aprobados: %d | Reprobados: %d\n", aprobados[j], reprobados[j]);
    }

    return 0;
}