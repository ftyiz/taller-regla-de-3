#include <stdio.h>
#include <string.h>

int main()
{
    int i, j, k;
    char estudiantes[5][30];
    char materias[3][30] = {"calculo", "programacion", "fisica"};
    float notas[5][3];
    float prom_estudiante, prom_materia[3] = {0};
    float max_estudiante, min_estudiante;
    float max_materia[3], min_materia[3];
    int aprobados[3] = {0}, reprobados[3] = {0};
    char buffer[100];
    float suma, nota_temp;
    int num_estudiantes = 5, num_materias = 3;
    int valido;

    

    for (j = 0; j < num_materias; j++)
    {
        max_materia[j] = 0;
        min_materia[j] = 10;
    }

    printf("=== GESTION DE CALIFICACIONES ===\n");
    printf("Materias cargadas:\n");
    for (j = 0; j < num_materias; j++)
    {
        printf(" - %s\n", materias[j]);
    }
    for (i = 0; i < num_estudiantes; i++)
    {
        do
        {
            printf("\nIngrese el nombre del estudiante %d: ", i + 1);
            fgets(estudiantes[i], sizeof(estudiantes[i]), stdin);
            estudiantes[i][strcspn(estudiantes[i], "\n")] = '\0';
            valido = 1;

            if (strlen(estudiantes[i]) == 0)
            {
                printf("Error: el nombre no puede estar vacio.\n");
                valido = 0;
            }
            else
            {
                int hay_letra = 0;
                for (k = 0; k < (int)strlen(estudiantes[i]); k++)
                {
                    char c = estudiantes[i][k];
                    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
                        hay_letra = 1;
                    else if (c != ' ')
                    {
                        printf("Error: el nombre solo puede tener letras y espacios.\n");
                        valido = 0;
                        break;
                    }
                }
                if (valido && !hay_letra)
                {
                    printf("Error: el nombre no puede ser solo espacios.\n");
                    valido = 0;
                }
            }
        } while (!valido);

        printf("\n--- Ingreso de notas para %s ---\n", estudiantes[i]);
        suma = 0;
        for (j = 0; j < num_materias; j++)
        {
            valido = 0;
            while (!valido)
            {
                printf("Ingrese la nota de %s en %s (0 a 10): ",
                       estudiantes[i], materias[j]);
                fgets(buffer, sizeof(buffer), stdin);
                buffer[strcspn(buffer, "\n")] = '\0';

                int lenbuf = (int)strlen(buffer);
                int solo_espacios = 1;
                for (k = 0; k < lenbuf; k++)
                {
                    if (buffer[k] != ' ')
                    {
                        solo_espacios = 0;
                        break;
                    }
                }

                if (lenbuf == 0 || solo_espacios)
                {
                    printf("Error: no puede dejar vacio. Ingrese un numero.\n");
                    continue;
                }

                valido = 1;
                int punto = 0;
                for (k = 0; k < lenbuf; k++)
                {
                    if ((buffer[k] >= '0' && buffer[k] <= '9') || buffer[k] == '.')
                    {
                        if (buffer[k] == '.')
                            punto++;
                        if (punto > 1)
                        {
                            valido = 0;
                            break;
                        }
                    }
                    else
                    {
                        valido = 0;
                        break;
                    }
                }

                if (!valido)
                {
                    printf("Error: ingrese solo numeros validos.\n");
                    continue;
                }

                if (sscanf(buffer, "%f", &nota_temp) != 1)
                {
                    printf("Error: no se pudo leer la nota.\n");
                    valido = 0;
                    continue;
                }

                if (nota_temp < 0 || nota_temp > 10)
                {
                    printf("Error: la nota debe estar entre 0 y 10.\n");
                    valido = 0;
                }
                else
                {
                    notas[i][j] = nota_temp;
                    valido = 1;
                }
            }
        }
        max_estudiante = notas[i][0];
        min_estudiante = notas[i][0];
        suma = 0;

        for (j = 0; j < num_materias; j++)
        {
            suma += notas[i][j];
            if (notas[i][j] > max_estudiante)
                max_estudiante = notas[i][j];
            if (notas[i][j] < min_estudiante)
                min_estudiante = notas[i][j];

            prom_materia[j] += notas[i][j];

            if (notas[i][j] > max_materia[j])
                max_materia[j] = notas[i][j];
            if (notas[i][j] < min_materia[j])
                min_materia[j] = notas[i][j];

            if (notas[i][j] >= 6.0)
                aprobados[j]++;
            else
                reprobados[j]++;
        }

        prom_estudiante = suma / num_materias;

        printf("\n=== RESULTADOS DE %s ===\n", estudiantes[i]);
        printf("Promedio general: %.2f\n", prom_estudiante);
        printf("Nota mas alta: %.2f\n", max_estudiante);
        printf("Nota mas baja: %.2f\n", min_estudiante);
        printf("-----------------------------\n");
    }
    printf("\n=== RESULTADOS GENERALES POR MATERIA ===\n");
    for (j = 0; j < num_materias; j++)
    {
        prom_materia[j] /= num_estudiantes;
        printf("\nMateria: %s\n", materias[j]);
        printf("Promedio general: %.2f\n", prom_materia[j]);
        printf("Nota mas alta: %.2f\n", max_materia[j]);
        printf("Nota mas baja: %.2f\n", min_materia[j]);
        printf("Aprobados (6-10): %d\n", aprobados[j]);
        printf("Reprobados (0-5.99): %d\n", reprobados[j]);
    }

    return 0;
}