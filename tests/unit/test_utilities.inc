#ifndef TEST_UTILITIES_INC
#define TEST_UTILITIES_INC

/*
 * This file contains functions that are useful when writing tests.
 * Include it in the test program using #include "test_utilities.inc"
 */

#include <igraph/igraph.h>
#include <stdio.h>
#include <string.h>

/* Print an igraph_real_t value. Be consistent in printing NaN/Inf across platforms. */
void print_real(FILE *f, igraph_real_t x, const char *format) {
    igraph_bool_t g8 = !strcmp(format, "%8g");
    if (igraph_finite(x)) {
        fprintf(f, format, x);
    } else if (igraph_is_nan(x)) {
        fprintf(f, g8 ? "     NaN" : "NaN");
    } else if (igraph_is_posinf(x)) {
        fprintf(f, g8 ? "     Inf" : "Inf");
    } else if (igraph_is_neginf(x)) {
        fprintf(f, g8 ? "    -Inf" : "-Inf");
    }
}

void print_vector_format(const igraph_vector_t *v, FILE *f, const char *format) {
    long i, n = igraph_vector_size(v);
    fprintf(f, "(");
    for (i=0; i < n; i++) {
        fprintf(f, " ");
        print_real(f, VECTOR(*v)[i], format);
    }
    fprintf(f, " )\n");
}

/* Print elements of a vector. Use parentheses to make it clear when a vector has size zero. */
void print_vector(const igraph_vector_t *v) {
    print_vector_format(v, stdout, "%g");
}

/* Print elements of a matrix. Use brackets to make it clear when a vector has size zero. */
void print_matrix_format(const igraph_matrix_t *m, FILE *f, const char *format) {
    long i, j, nrow = igraph_matrix_nrow(m), ncol = igraph_matrix_ncol(m);
    for (i = 0; i < nrow; i++) {
        fprintf(f, i == 0 ? "[" : " ");
        for (j = 0; j < ncol; j++) {
            fprintf(f, " ");
            print_real(f, MATRIX(*m, i, j), format);
        }
        fprintf(f, i == nrow-1 ? " ]\n" : "\n");
    }
}

void print_matrix(const igraph_matrix_t *m) {
    print_matrix_format(m, stdout, "%8g");
}

/* Print a matrix, ensuring that the first nonzero element in each column is
 * positive. */
void print_matrix_first_row_positive(const igraph_matrix_t *matrix, const char* format) {
    igraph_matrix_t copy;
    long i, j, nrow, ncol;

    igraph_matrix_init_copy(&copy, matrix);

    nrow = igraph_matrix_nrow(&copy);
    ncol = igraph_matrix_ncol(&copy);

    for (i = 0; i < ncol; i++) {
        for (j = 0; j < nrow; j++) {
            if (MATRIX(copy, j, i) < 0) {
                for (; j < nrow; j++) {
                    if (MATRIX(copy, j, i) != 0) {
                        MATRIX(copy, j, i) *= -1;
                    }
                }
                break;
            } else if (MATRIX(copy, j, i) > 0) {
                break;
            }
        }
    }

    igraph_matrix_printf(&copy, format);
    igraph_matrix_destroy(&copy);
}

/* Print a complex matrix, ensuring that the first element with nonzero real
 * part in each column has a positive real part. */
void print_matrix_complex_first_row_positive(const igraph_matrix_complex_t *matrix) {
    igraph_matrix_complex_t copy;
    long i, j, nrow, ncol;
    igraph_complex_t z;
    char buf[256];
    size_t len;

    igraph_matrix_complex_init_copy(&copy, matrix);

    nrow = igraph_matrix_complex_nrow(&copy);
    ncol = igraph_matrix_complex_ncol(&copy);

    for (i = 0; i < ncol; i++) {
        for (j = 0; j < nrow; j++) {
            if (IGRAPH_REAL(MATRIX(copy, j, i)) < 0) {
                for (; j < nrow; j++) {
                    if (IGRAPH_REAL(MATRIX(copy, j, i)) != 0) {
                        IGRAPH_REAL(MATRIX(copy, j, i)) *= -1;
                    }
                    if (IGRAPH_IMAG(MATRIX(copy, j, i)) != 0) {
                        IGRAPH_IMAG(MATRIX(copy, j, i)) *= -1;
                    }
                }
                break;
            } else if (IGRAPH_REAL(MATRIX(copy, j, i)) > 0) {
                break;
            }
        }
    }

    for (i = 0; i < nrow; i++) {
        for (j = 0; j < ncol; j++) {
            z = MATRIX(copy, i, j);
            if (j != 0) {
                putchar(' ');
            }

            snprintf(buf, sizeof(buf), "%g%+gi", IGRAPH_REAL(z), IGRAPH_IMAG(z));
            len = strlen(buf);

            /* ensure that we don't print -0 in the imaginary part */
            if (len > 3 && buf[len-3] == '-' && buf[len-2] == '0' && buf[len-1] == 'i') {
              buf[len-3] = '+';
            }

            /* ensure that we don't print -0 in the real part either */
            if (buf[0] == '-' && buf[1] == '0' && (buf[2] == '+' || buf[2] == '-')) {
                printf("%s", buf + 1);
            } else {
                printf("%s", buf);
            }
        }
        printf("\n");
    }

    igraph_matrix_complex_destroy(&copy);
}

#define VERIFY_FINALLY_STACK() \
    if (!IGRAPH_FINALLY_STACK_EMPTY) { \
        printf( \
          "Finally stack is not empty. " \
          "Check that the number in IGRAPH_FINALLY_CLEAN matches the IGRAPH_FINALLY count.\n"); \
        return 100; \
    }

#endif /* TEST_UTILITIES_INC */
