#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char** string_to_matrix(const char* input, int* word_count) {
    int count = 0;
    int in_word = 0;
    int in_quotes = 0;
    char quote_char = '\0';
    
    // Count words
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '"' || input[i] == '\'') {
            if (!in_quotes) {
                in_quotes = 1;
                quote_char = input[i];
                if (!in_word) {
                    count++;
                    in_word = 1;
                }
            } else if (input[i] == quote_char) {
                in_quotes = 0;
                quote_char = '\0';
            }
        } else if (isspace(input[i])) {
            if (!in_quotes) {
                in_word = 0;
            }
        } else {
            if (!in_word) {
                count++;
                in_word = 1;
            }
        }
    }
    
    // Allocate matrix
    char** matrix = (char**)malloc(count * sizeof(char*));
    if (matrix == NULL) {
        *word_count = 0;
        return NULL;
    }
    
    // Extract words
    int word_index = 0;
    in_word = 0;
    in_quotes = 0;
    quote_char = '\0';
    char* word = NULL;
    int word_len = 0;
    int word_capacity = 0;
    
    for (int i = 0; input[i] != '\0'; i++) {
        if (input[i] == '"' || input[i] == '\'') {
            if (!in_quotes) {
                in_quotes = 1;
                quote_char = input[i];
                if (!in_word) {
                    in_word = 1;
                    word_len = 0;
                    word_capacity = 16; // Initial capacity
                    word = (char*)malloc(word_capacity * sizeof(char));
                    if (word == NULL) {
                        // Handle allocation failure
                        for (int j = 0; j < word_index; j++) {
                            free(matrix[j]);
                        }
                        free(matrix);
                        *word_count = 0;
                        return NULL;
                    }
                }
            } else if (input[i] == quote_char) {
                in_quotes = 0;
                quote_char = '\0';
            } else {
                if (word_len + 1 >= word_capacity) {
                    word_capacity *= 2;
                    char* new_word = (char*)realloc(word, word_capacity * sizeof(char));
                    if (new_word == NULL) {
                        // Handle reallocation failure
                        free(word);
                        for (int j = 0; j < word_index; j++) {
                            free(matrix[j]);
                        }
                        free(matrix);
                        *word_count = 0;
                        return NULL;
                    }
                    word = new_word;
                }
                word[word_len++] = input[i];
            }
        } else if (isspace(input[i])) {
            if (!in_quotes) {
                if (in_word) {
                    word[word_len] = '\0';
                    matrix[word_index] = word;
                    word_index++;
                    in_word = 0;
                    word = NULL;
                    word_len = 0;
                    word_capacity = 0;
                }
            } else {
                if (word_len + 1 >= word_capacity) {
                    word_capacity *= 2;
                    char* new_word = (char*)realloc(word, word_capacity * sizeof(char));
                    if (new_word == NULL) {
                        // Handle reallocation failure
                        free(word);
                        for (int j = 0; j < word_index; j++) {
                            free(matrix[j]);
                        }
                        free(matrix);
                        *word_count = 0;
                        return NULL;
                    }
                    word = new_word;
                }
                word[word_len++] = input[i];
            }
        } else {
            if (!in_word) {
                in_word = 1;
                word_len = 0;
                word_capacity = 16; // Initial capacity
                word = (char*)malloc(word_capacity * sizeof(char));
                if (word == NULL) {
                    // Handle allocation failure
                    for (int j = 0; j < word_index; j++) {
                        free(matrix[j]);
                    }
                    free(matrix);
                    *word_count = 0;
                    return NULL;
                }
            }
            if (word_len + 1 >= word_capacity) {
                word_capacity *= 2;
                char* new_word = (char*)realloc(word, word_capacity * sizeof(char));
                if (new_word == NULL) {
                    // Handle reallocation failure
                    free(word);
                    for (int j = 0; j < word_index; j++) {
                        free(matrix[j]);
                    }
                    free(matrix);
                    *word_count = 0;
                    return NULL;
                }
                word = new_word;
            }
            word[word_len++] = input[i];
        }
    }
    
    // Handle last word
    if (in_word) {
        word[word_len] = '\0';
        matrix[word_index] = word;
    }
    
    *word_count = count;
    return matrix;
}

void free_matrix(char** matrix, int word_count) {
    for (int i = 0; i < word_count; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Main function to test string_to_matrix
int main() {
    const char* test_strings[] = {
        "This is a simple test",
        "\"Hudson\" is a name",
        "This is a \"test string\" with 'quotes'",
        "'Hudson' is \"'quoted'\" differently",
        "Mixed \"double\" and 'single' quotes",
        "Nested \"'quotes'\" and '\"quotes\"'",
        "Empty \"\" and '' quotes",
        "   Extra   spaces   between   words   ",
        "\"Quoted string with spaces\"",
        "No quotes at all",
        "A very long word: abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789"
    };
    int num_tests = sizeof(test_strings) / sizeof(test_strings[0]);

    for (int i = 0; i < num_tests; i++) {
        int word_count;
        char** result = string_to_matrix(test_strings[i], &word_count);

        printf("Test %d:\n", i + 1);
        printf("Input: %s\n", test_strings[i]);
        printf("Word count: %d\n", word_count);
        printf("Output:\n");
        for (int j = 0; j < word_count; j++) {
            printf("  [%d]: \"%s\"\n", j, result[j]);
        }
        printf("\n");

        free_matrix(result, word_count);
    }

    return 0;
}