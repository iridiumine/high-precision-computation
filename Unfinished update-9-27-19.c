#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ElementType char
#define MAXSIZE 400

int flag = 0;

typedef struct LNode *List;
struct LNode {
    ElementType Data;
    List Next;
};

List PtrL, X, Y, X1, X2;

List MakeEmpty() {
    List PtrL;
    
    PtrL = (List)malloc(sizeof(struct LNode));
    
    return PtrL;
}

int Length(List PtrL) {
    List p = PtrL;
    
    int length = 0;
    
    while (p) {
        p = p->Next;
        length++;
    }
    
    return length;
}

int Distance_point(List PtrL) {
    int distance = 0;
    List p = PtrL;
    
    while (p != NULL && p->Data != '.') {
        p = p->Next;
        distance++;
    }
    
    return distance;
}

List Find_point(List PtrL) {
    List p = PtrL;
    
    while (p != NULL && p->Data != '.') {
        p = p->Next;
    }
    
    return p;
}

List Find_Kth(int K, List PtrL) {
    List p = PtrL;
    
    int i = 1;
    
    while (p != NULL && i < K) {
        p = p->Next;
        i++;
    }
    
    if (i == K) {
        return p;
    }
    else {
        return NULL;
    }
}

int Find_Kth_number(int K, List PtrL) {
    List p = PtrL;
    
    int i = 1;
    
    while (p != NULL && i < K) {
        p = p->Next;
        i++;
    }
    
    if (i == K) {
        return p->Data - '0';
    }
    else {
        return -1;
    }
}

void Insert_zero_before(List PtrL) {
    List p = (List)malloc(sizeof(struct LNode));
    
    p->Data = '0';
    p->Next = PtrL->Next;
    PtrL->Next = p;
}

void Insert_zero_after(List PtrL) {
    List p = (List)malloc(sizeof(struct LNode));
    
    p->Data = '0';
    p->Next = NULL;
    PtrL->Next = p;
}

void Change(int item, int K, List PtrL) {
    List p = Find_Kth(K, PtrL);
    
    p->Data = item + '0';
}

List Insert(ElementType x, List PtrL) {
    List p = (List)malloc(sizeof(struct LNode));
    
    p->Data = x;
    p->Next = NULL;
    PtrL->Next = p;
    
    return p;
}

List Insert_Kth(ElementType X, int K, List PtrL) {
    List p, s;
    
    if (K == 1) {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = PtrL;
        return s;
    }
    
    p = Find_Kth(K-1, PtrL);
    
    if (p == NULL) {
        printf("wrong parameter K\n");
        return NULL;
    }
    else {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = p->Next;
        p->Next = s;
        return PtrL;
    }
}

void Move(List PtrL) {
    int d1 = Distance_point(PtrL);
    
    while (d1 < 200) {
        Insert_zero_before(PtrL);
        d1++;
    }
    
    int d2 = Length(PtrL);
    
    for (; d2 < 400; d2++) {
        List p = Find_Kth(d2, PtrL);
        Insert_zero_after(p);
    }
}

List Write_without_Move(List PtrL) {
    char c;
    List p = PtrL;
    
    while ((c = getchar()) != '\n') {
        Insert(c, p);
        int i = Length(PtrL);
        p = Find_Kth(i, PtrL);
    }
    
    return PtrL;
}

List Write_with_Move(List PtrL) {
    char c;
    List p = PtrL;
    
    while ((c = getchar()) != '\n') {
        Insert(c, p);
        int i = Length(PtrL);
        p = Find_Kth(i, PtrL);
    }
    
    Move(PtrL);
    
    return PtrL;
}

void Print_without_Move(List PtrL) {
    List p = PtrL;
    
    while (p) {
        printf("%c", p->Data);
        p = p->Next;
    }
    
    printf("\n");
}

void Print_with_Move(List PtrL) {
    int i, j;
    int flag1 = -1, flag2 = -1;
    
    for (i = 2; i < 201; i++) {
        List p = Find_Kth(i, PtrL);
        if (p->Data != '0') {
            flag1 = 0;
        }
        if (flag1 == 0 || (flag1 == -1 && i == 200)) {
            printf("%c", p->Data);
        }
        p = p->Next;
    }
    
    for (j = 399; j > 202; j--) {
        List p = Find_Kth(j, PtrL);
        if (p->Data != '0') {
            flag2 = 0;
            break;
        }
    }
    
    for (i = 201; i <= j; i++) {
        List p = Find_Kth(i, PtrL);
        printf("%c", p->Data);
    }
    
    printf("\n");
}

List Add(List X1, List X2) {
    List p = MakeEmpty();
    List q = (List)malloc(sizeof(struct LNode));
    
    int i;
    
    p->Next = q;
    q->Data = '.';
    q->Next = NULL;
    
    Move(p);
    
    for (i = 200; i >= 1; i--) {
        if (i == 200) {
            int a1 = Find_Kth_number(202, X1);
            int b1 = Find_Kth_number(202, X2);
            int sum1 = a1 + b1;
            if (sum1 >= 10) {
                flag = 1;
            }
        }
        int a = Find_Kth_number(i, X1);
        int b = Find_Kth_number(i, X2);
        int sum = a + b + flag;
        flag = 0;
        if (sum >= 10) {
            flag = 1;
            sum = sum - 10;
        }
        Change(sum, i, p);
    }
    
    for (i = 399; i >= 202; i--) {
        int a = Find_Kth_number(i, X1);
        int b = Find_Kth_number(i, X2);
        int sum = a + b + flag;
        flag = 0;
        if (sum >= 10) {
            flag = 1;
            sum = sum - 10;
        }
        Change(sum, i, p);
    }
    
    return p;
}

List Subtract(List X1, List X2) {
    List p = MakeEmpty();
    List q = (List)malloc(sizeof(struct LNode));
    
    int i;
    
    p->Next = q;
    q->Data = '.';
    q->Next = NULL;
    
    Move(p);
    
    for (i = 399; i >= 202; i--) {
        int a = Find_Kth_number(i, X1);
        int b = Find_Kth_number(i, X2);
        int subtraction = a - b + flag;
        flag = 0;
        if (subtraction < 0) {
            subtraction = subtraction + 10;
            flag = -1;
        }
        Change(subtraction, i, p);
    }
    
    for (i = 200; i >= 1; i--) {
        int a = Find_Kth_number(i, X1);
        int b = Find_Kth_number(i, X2);
        int subtraction = a - b + flag;
        flag = 0;
        if (subtraction < 0) {
            subtraction = subtraction + 10;
            flag = -1;
        }
        Change(subtraction, i, p);
    }
    
    if (flag == -1) {
        printf("-");
        flag = 0;
        return Subtract(X2, X1);
    }
    
    return p;
}

List Multiply(List X1, List X2) {
    char temp1[MAXSIZE];
    char temp2[MAXSIZE];
    
    memset(temp1, 0, sizeof(temp1));
    memset(temp2, 0, sizeof(temp2));
    
    int m, n, u = 0, v = 0, flag = 0, sum = 0;
    
    if (Find_point(X1) == NULL) {
        int tail = Length(X1);
        Insert_Kth('.', tail+1, X1);
        Insert_Kth('0', tail+2, X1);
    }
    
    if (Find_point(X2) == NULL) {
        int tail = Length(X2);
        Insert_Kth('.', tail+1, X2);
        Insert_Kth('0', tail+2, X2);
    }
    
    int i1 = Length(X1);
    int i2 = Length(X2);
    
    m = i1 - 2;
    n = i2 - 2;
    int tempt = m - 1;
    if (Find_point(X1) != NULL) {
        for (; i1 > 1; i1--) {
            if (Find_Kth_number(i1, X1) != -2) {
                if (flag == 0) {
                    u++;
                }
                temp1[tempt] = Find_Kth_number(i1, X1) + '0';
                tempt--;
            }
            else {
                flag = 1;
            }
        }
    }
    
    tempt = n - 1;
    flag = 0;
    
    if (Find_point(X2) != NULL) {
        for (; i2 > 1; i2--) {
            if (Find_Kth_number(i2, X2) != -2) {
                if (flag == 0) {
                    v++;
                }
                temp2[tempt] = Find_Kth_number(i2, X2) + '0';
                tempt--;
            }
            else {
                flag = 1;
            }
        }
    }
    sum = u + v;
    
    int temp[2 * MAXSIZE];
    int i, j, k = 0, t;
    
    memset(temp, 0, sizeof(temp));
    
    for (i = n-1; i >= 0; i--) {
        for (j = m-1; j >= 0; j--) {
            t = 2 * MAXSIZE - m - n + i + j + 1;
            
            temp[t] = (temp2[i] - '0') * (temp1[j] - '0') + temp[t];
            
            if (temp[t] >= 10) {
                int tep = temp[t];
                temp[t] = tep % 10;
                temp[t-1] = tep / 10 + temp[t-1];
            }
        }
    }
    
    while (temp[k] == 0) {
        k++;
    }
    
    PtrL = MakeEmpty();
    
    List p = PtrL;
    
    for (size_t t = k; t < 2 * MAXSIZE; t++) {
        if (temp[t] >= 0 && temp[t] <= 9) {
            Insert(temp[t] + '0', p);
            int i = Length(PtrL);
            p = Find_Kth(i, PtrL);
        }
    }
    
    int size = Length(PtrL);
    
    Insert_Kth('.', size - sum + 1, PtrL);
    
    return PtrL;
}

List SysConvert(List X, int K) {
    List part1, part2, point;
    int point_location, rear, i, j = 0;
    
    part1 = MakeEmpty();
    part2 = MakeEmpty();
    
    point = Find_point(X);
    
    point_location = Distance_point(X);
    rear = Length(X);
    
    int size_part1 = point_location, size_part2 = rear - point_location;
    char temp1[size_part1];
    char unknown[size_part1];
    char quotient[size_part1];
    char output1[MAXSIZE];
    char zero[size_part1];
    char temp2[size_part2];
    
    memset(temp1, 0, sizeof(temp1));
    memset(unknown, 0, sizeof(unknown));
    memset(quotient, 0, sizeof(quotient));
    memset(output1, 0, sizeof(output1));
    memset(zero, 0, sizeof(zero));
    memset(temp2, 0, sizeof(temp2));
    
    for (i = 2; i <= point_location; i++) {
        temp1[j] = Find_Kth_number(i, X) + '0';
        j++;
    }
    
    int k;
    for (k = 0; k < size_part1 - 2; k++) {
        unknown[k] = '0';
    }
    unknown[size_part1-1] = '\0';
    unknown[size_part1-2] = '0' + K;
    
    temp1[size_part1-1] = '\0';
    
    for (k = 0; k <= size_part1 - 2; k++) {
        quotient[k] = '0';
    }
    quotient[size_part1-1] = '\0';
    
    for (k = 0; k <= size_part1 - 2; k++) {
        zero[k] = '0';
    }
    zero[size_part1-1] = '\0';
    
    output1[MAXSIZE-1] = '\0';
    int precedence = MAXSIZE - 2;
    
    int flag = 1;
    while (flag == 1 || strcmp(quotient, zero) > 0) {
        if (flag == 1) {
            flag = 0;
        }
        else {
            strcpy(temp1, quotient);
            for (k = 0; k <= size_part1 - 2; k++) {
                quotient[k] = '0';
            }
            quotient[size_part1-1] = '\0';
        }
        
        while (strcmp(temp1, unknown) >= 0) {
            int u;
            for (u = size_part1 - 2; u >= 0; u--) {
                int temp_number = temp1[u] - unknown[u];
                if (temp_number < 0) {
                    temp1[u] = temp_number + 10 +'0';
                    temp1[u-1] = temp1[u-1] - 1;
                }
                else {
                    temp1[u] = temp_number + '0';
                }
            }
            
            quotient[size_part1-2] = quotient[size_part1-2] + 1;
            int v;
            for (v = size_part1 - 2; v >= 0; v--) {
                if ((quotient[v] - '0') >= 10) {
                    quotient[v] = quotient[v] - 10;
                    quotient[v-1] = quotient[v-1] + 1;
                }
            }
        }
        
        output1[precedence] = temp1[size_part1-2];
        precedence--;
    }
    
    for (size_t i = 0; i < MAXSIZE; i++) {
        printf("%c", output1[i]);
    }
    printf("\n");
    
    j = 0;
    
    for (i = point_location + 2; i <= rear; i++) {
        temp2[j] = Find_Kth_number(i, X) + '0';
        j++;
    }
    
    List p = X;
    
    return p;
}

int main(int argc, char const *argv[]) {
    
}
