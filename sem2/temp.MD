#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    printf("Enter a string: ");
    gets(str);
    printf("Length of the string is: %lu\n", strlen(str));
    return 0;
}




#include <stdio.h>

int main() {
    char str[100];
    int i = 0;
    printf("Enter a string: ");
    gets(str);
    while (str[i] != '\0') {
        i++;
    }
    printf("Length of the string is: %d\n", i);
    return 0;
}





#include <stdio.h>

int main() {
    char str[100];
    char *ptr;
    int length = 0;
    printf("Enter a string: ");
    gets(str);
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
    char str1[100], str2[100];
    printf("Enter first string: ");
    gets(str1);
    printf("Enter second string: ");
    gets(str2);
    strcat(str1, str2);
    printf("Concatenated string: %s\n", str1);
    return 0;
}



#include <stdio.h>

int main() {
    char str1[100], str2[100];
    int i = 0, j = 0;
    printf("Enter first string: ");
    gets(str1);
    printf("Enter second string: ");
    gets(str2);
    while (str1[i] != '\0') {
        i++;
    }
    while (str2[j] != '\0') {
        str1[i] = str2[j];
        i++;
        j++;
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
    gets(source);
    strcpy(destination, source);
    printf("Copied string: %s\n", destination);
    return 0;
}





#include <stdio.h>

int main() {
    char source[100], destination[100];
    int i = 0;
    printf("Enter source string: ");
    gets(source);
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
    gets(str1);
    printf("Enter second string: ");
    gets(str2);
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
    gets(str);
    while (str[len] != '\0') {
        len++;
    }
    for (i = len - 1; i >= 0; i--) {
        rev[j++] = str[i];
    }
    rev[j] = '\0';
    i = 0;
    while (str[i] != '\0') {
        if (str[i] != rev[i]) {
            flag = 1;
            break;
        }
        i++;
    }
    printf("Reversed string: %s\n", rev);
    if (flag == 0)
        printf("The string is a palindrome.\n");
    else
        printf("The string is not a palindrome.\n");
    return 0;
}


