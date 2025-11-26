#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    printf("Length of the string is: %lu\n", strlen(str));
    return 0;
}



#include <stdio.h>

int main() {
    char str[100];
    int i = 0;
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    while (str[i] != '\0') {
        i++;
    }
    printf("Length of the string is: %d\n", i);
    return 0;
}



#include <stdio.h>

int main() {
    char str[100], *ptr;
    int length = 0;
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    ptr = str;
    while (*ptr != '\0') {
        length++;
        ptr++;
    }
    printf("Length of the string is: %d\n", length);
    return 0;
}




#include <stdio.h>
#include <string.h>

int main() {
    char str1[200], str2[100];
    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);
    str1[strcspn(str1, "\n")] = '\0';
    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);
    str2[strcspn(str2, "\n")] = '\0';
    strcat(str1, str2);
    printf("Concatenated string: %s\n", str1);
    return 0;
}




#include <stdio.h>

int main() {
    char str1[200], str2[100];
    int i = 0, j = 0;
    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);
    str1[strcspn(str1, "\n")] = '\0';
    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);
    str2[strcspn(str2, "\n")] = '\0';
    while (str1[i] != '\0') {
        i++;
    }
    while (str2[j] != '\0') {
        str1[i++] = str2[j++];
    }
    str1[i] = '\0';
    printf("Concatenated string: %s\n", str1);
    return 0;
}





#include <stdio.h>
#include <string.h>

int main() {
    char source[100], destination[100];
    printf("Enter source string: ");
    fgets(source, sizeof(source), stdin);
    source[strcspn(source, "\n")] = '\0';
    strcpy(destination, source);
    printf("Copied string: %s\n", destination);
    return 0;
}




#include <stdio.h>

int main() {
    char source[100], destination[100];
    int i = 0;
    printf("Enter source string: ");
    fgets(source, sizeof(source), stdin);
    source[strcspn(source, "\n")] = '\0';
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
    printf("Copied string: %s\n", destination);
    return 0;
}






#include <stdio.h>

int main() {
    char str1[100], str2[100];
    int i = 0, flag = 0;
    printf("Enter first string: ");
    fgets(str1, sizeof(str1), stdin);
    str1[strcspn(str1, "\n")] = '\0';
    printf("Enter second string: ");
    fgets(str2, sizeof(str2), stdin);
    str2[strcspn(str2, "\n")] = '\0';
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            flag = 1;
            break;
        }
        i++;
    }
    if (str1[i] != str2[i])
        flag = 1;
    if (flag == 0)
        printf("Strings are equal.\n");
    else
        printf("Strings are not equal.\n");
    return 0;
}





#include <stdio.h>

int main() {
    char str[100], rev[100];
    int i = 0, j = 0, len = 0, flag = 0;
    printf("Enter a string: ");
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    while (str[len] != '\0') {
        len++;
    }
    for (i = len - 1; i >= 0; i--) {
        rev[j++] = str[i];
    }
    rev[j] = '\0';
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != rev[i]) {
            flag = 1;
            break;
        }
    }
    printf("Reversed string: %s\n", rev);
    if (flag == 0)
        printf("The string is a palindrome.\n");
    else
        printf("The string is not a palindrome.\n");
    return 0;
}
