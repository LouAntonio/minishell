#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assumindo que estas definições estão em um arquivo de cabeçalho
typedef enum {
    TOKEN_ARG,
    TOKEN_PIPE,
    TOKEN_APPEND_OUT,
    TOKEN_REDIRECT_OUT,
    TOKEN_HEREDOC,
    TOKEN_REDIRECT_IN,
    TOKEN_COMMAND
} TokenType;

typedef struct {
    TokenType type;
    char *value;
} Token;

// Protótipos de funções
Token **classify_tokens(char **tokens, int word_count);
TokenType identify_token(char *token);

// Função para imprimir os tokens classificados
void print_classified_tokens(Token **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        printf("Token %d: Value = '%s', Type = ", i, tokens[i]->value);
        switch (tokens[i]->type) {
            case TOKEN_ARG: printf("ARG\n"); break;
            case TOKEN_PIPE: printf("PIPE\n"); break;
            case TOKEN_APPEND_OUT: printf("APPEND_OUT\n"); break;
            case TOKEN_REDIRECT_OUT: printf("REDIRECT_OUT\n"); break;
            case TOKEN_HEREDOC: printf("HEREDOC\n"); break;
            case TOKEN_REDIRECT_IN: printf("REDIRECT_IN\n"); break;
            case TOKEN_COMMAND: printf("COMMAND\n"); break;
            default: printf("UNKNOWN\n");
        }
    }
    printf("\n");
}

// Função para liberar a memória alocada para os tokens
void free_classified_tokens(Token **tokens) {
    for (int i = 0; tokens[i] != NULL; i++) {
        free(tokens[i]);
    }
    free(tokens);
}

// Função main com testes
int main() {
    char **test_cases[] = {
        (char *[]){"ls", "-l", "|", "grep", "file", NULL},
        (char *[]){"echo", "Hello", ">", "output.txt", NULL},
        (char *[]){"cat", "input.txt", ">>", "output.txt", NULL},
        (char *[]){"command1", "|", "command2", "|", "command3", NULL},
        (char *[]){"grep", "pattern", "<<", "EOF", NULL},
        (char *[]){"single_command", NULL},
        NULL
    };

    for (int i = 0; test_cases[i] != NULL; i++) {
        printf("Test Case %d:\n", i + 1);
        
        // Contar o número de palavras
        int word_count = 0;
        while (test_cases[i][word_count] != NULL) {
            word_count++;
        }

        // Classificar os tokens
        Token **classified = classify_tokens(test_cases[i], word_count);

        // Imprimir os resultados
        if (classified) {
            print_classified_tokens(classified);
            free_classified_tokens(classified);
        } else {
            printf("Error: Failed to classify tokens.\n\n");
        }
    }

    return 0;
}

TokenType	identify_token(char *token)
{
	if (strncmp(token, "|", 1) == 0)
		return (TOKEN_PIPE);
	else if (strncmp(token, ">>", 2) == 0)
		return (TOKEN_APPEND_OUT);
	else if (strncmp(token, ">", 1) == 0)
		return (TOKEN_REDIRECT_OUT);
	else if (strncmp(token, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	else if (strncmp(token, "<", 1) == 0)
		return (TOKEN_REDIRECT_IN);
	return (TOKEN_ARG);
}
Token **classify_tokens(char **tokens, int word_count)
{
    Token **classified_tokens;
    int i;

    classified_tokens = malloc((word_count + 1) * sizeof(Token *));
    if (!classified_tokens)
        return NULL;

    for (i = 0; tokens[i] != NULL; i++)
    {
        classified_tokens[i] = malloc(sizeof(Token));
        if (!classified_tokens[i])
        {
            // Free previously allocated memory
            while (--i >= 0)
                free(classified_tokens[i]);
            free(classified_tokens);
            return NULL;
        }

        classified_tokens[i]->value = tokens[i];
        classified_tokens[i]->type = identify_token(tokens[i]);

        // If the token is an argument and follows a pipe, it's a command
        if (classified_tokens[i]->type == TOKEN_ARG && i > 0 && 
            classified_tokens[i-1]->type == TOKEN_PIPE)
        {
            classified_tokens[i]->type = TOKEN_COMMAND;
        }
        // If it's the first token and an argument, it's a command
        else if (classified_tokens[i]->type == TOKEN_ARG && i == 0)
        {
            classified_tokens[i]->type = TOKEN_COMMAND;
        }
    }

    classified_tokens[i] = NULL;
    return classified_tokens;
}