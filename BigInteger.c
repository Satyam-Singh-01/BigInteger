#include "BigInteger.h"

void addatfront(struct node** A, int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (!temp) {
        printf("Memory allocation failed\n");
        return;
    }
    temp->data = data;
    temp->next = *A;
    *A = temp;
}
struct BigInteger initialize(char* s) {
    struct BigInteger A;
    A.l = NULL;
    A.length = 0;
    A.sign = 1;

    if (s[0] == '-') {
        A.sign = -1;
        s++; // Move past the negative sign
    }
    int l=strlen(s);
    for (int i = (s[0] == '-' ? 1 : 0); i < l; i++) {
        if (s[i] >= '0' && s[i] <= '9') {
            addatfront(&(A.l), (s[i] - '0'));
            A.length++;
        }
    }

    return A;
}
void display(struct BigInteger A) {
    if (A.sign == -1) {
        printf("-");
    }

    if (!A.l) {
        printf("0\n");
        return;
    }

    // Count the number of digits to determine the required buffer size
    int numDigits = A.length;
    int buffer_size = numDigits + 1;  // +1 for the null terminator
    char* displayStr = (char*)malloc(buffer_size);
    if (!displayStr) {
        printf("Memory allocation failed\n");
        return;
    }

    struct node* current = A.l;
    int i = 0;
    while (current) {
        displayStr[i] = current->data + '0';
        current = current->next;
        i++;
    }
    displayStr[i] = '\0';

    printf("%s\n", displayStr);
    free(displayStr);
}
struct node* reverse(struct node* head) {
    struct node* temp1 = NULL;
    struct node* temp2 = NULL;
    while (head != NULL) {
        temp2 = (head)->next;
        (head)->next = temp1;
        temp1 = head;
        (head) = temp2;
    }
    head = temp1;
    return temp1;
}
int compare(struct BigInteger A, struct BigInteger B) {
   

    
    if (A.length > B.length) {
        return 1;
    } else if (A.length < B.length) {
        return -1;
    } else {
        int res=0;
        struct node* itr1=A.l;
        struct node* itr2= B.l;
        while(itr1!=NULL)
        {
            if(itr1->data > itr2->data)
            {
                res=1;
            }
            else if(itr1->data < itr2->data)
            {
                res=-1;
            }
            itr1=itr1->next;
            itr2=itr2->next;

        }
        return res;
    }
}
// struct BigInteger length(struct BigInteger A)
// {
//     int l=0;
//     struct node *temp=A.l;
//     while(temp)
//     {
//         l++;
//         temp=temp->next;
//     }
//     A.length=l;
//     return A;
// }
struct BigInteger add(struct BigInteger A, struct BigInteger B) {
    struct BigInteger result;
    result.l = NULL;
    result.length = 0;
     if(B.length>A.length)
    {
        struct BigInteger temp = A;
        A=B;
        B=temp;
    }

    // Determine the sign based on the conditions
    if (A.sign == -1 && B.sign == -1) {
        result.sign = -1; // Both inputs are negative
    } else if (A.sign == 1 && B.sign == 1) {
        result.sign = 1; // Both inputs are positive
    }
    else if (A.sign == -1 && B.sign == 1) {
        if(compare(A,B)==1)
        {
            
            A.sign=1;
            result=sub(A,B);
            result.sign=-1;
            return result;
        }
        else{
            
            A.sign=1;
            result=sub(B,A);
            result.sign=1;
            return result;
        }
    }
    else {
        if(compare(A,B)==1)
        {
            
            B.sign=1;
            result=sub(A,B);
            result.sign=1;
            return result;
        }
        else
        {
            
            B.sign=1;
            result=sub(B,A);
            result.sign=-1;
            return result;
        }
    }

    int carry = 0;
    struct node* p1 = A.l;
    struct node* p2 = B.l;

    while (p1 || p2) {
        int val1 = (p1) ? p1->data : 0;
        int val2 = (p2) ? p2->data : 0;

        int sum = carry + val1 + val2;
        carry = sum / 10;
        addatfront(&(result.l), sum % 10);
        result.length++;

        if (p1) p1 = p1->next;
        if (p2) p2 = p2->next;
    }

    if (carry > 0) {
        addatfront(&(result.l), carry);
        result.length++;
    }
    // Remove leading zeros
    while (result.l && result.l->data == 0) {
        struct node* temp = result.l;
        result.l = result.l->next;
        free(temp);
        result.length--;
    }
    return result;
}
struct BigInteger sub(struct BigInteger A, struct BigInteger B) {
    struct BigInteger result;
    result.l = NULL;
    result.length = 0;

    if (B.length > A.length) {
        // Swap n1 and n2, so n1 always represents the larger absolute value
        struct BigInteger temp = A;
        A = B;
        B = temp;
    }

    // Determine the sign based on the conditions
    if (A.sign == -1 && B.sign == -1) 
    {
        
         if(compare(A,B)==1)
        {
            result.sign=-1;
            
        }
        else{
            result.sign=1;
            struct BigInteger temp = A;
            A = B;
            B = temp;
        }
    } 
    else if (A.sign == 1 && B.sign == 1)
    {
         if(compare(A,B)==1)
        {
            result.sign=1;
        }
        else{
            result.sign=-1;
            struct BigInteger temp = A;
            A = B;
            B = temp;
        }
    }
    else if(A.sign==1 && B.sign==-1)
    {
        B.sign=1;
        result.sign=1;
        result=add(A,B);
        return result;

    }
    else
    {
        B.sign=-1;
        result.sign=-1;
        result=add(A,B);
        return result;
    }
    
    int borrow = 0;
    struct node* p1 = A.l;
    struct node* p2 = B.l;

    while (p1 || p2) {
        int val1 = (p1) ? p1->data : 0;
        int val2 = (p2) ? p2->data : 0;

        int diff = val1 - val2-borrow;

        if (diff<0) {
            borrow = 1;
            diff += 10;  // Borrow from the next digit
        } else {
            borrow = 0;
        }
        addatfront(&(result.l), diff);
        result.length++;
        if (p1) p1 = p1->next;
        if (p2) p2 = p2->next;
    }

    // Remove leading zeros
    while (result.l && result.l->data == 0) {
        struct node* temp = result.l;
        result.l = result.l->next;
        free(temp);
        result.length--;
    }

    return result;
}
struct BigInteger mul(struct BigInteger num1, struct BigInteger num2) {
    struct BigInteger result;
    result.l = NULL;
    result.length = 0;
    result.sign = (num1.sign == num2.sign) ? 1 : -1; // Determine the sign of the result

    if (num1.length == 0 || num2.length == 0) {
        // If either input is empty, the product is also empty
        return result;
    }

    // Create an array to store intermediate results for each digit
    int* intermediate = (int*)calloc(num1.length + num2.length, sizeof(int));

    if (!intermediate) {
        printf("Memory allocation failed\n");
        return result;
    }

    struct node* p1 = num1.l;
    int index1 = 0;

    while (p1) {
        int carry = 0;
        struct node* p2 = num2.l;
        int index2 = 0;

        while (p2) {
            intermediate[index1 + index2] += (p1->data * p2->data) + carry;
            carry = intermediate[index1 + index2] / 10;
            intermediate[index1 + index2] %= 10;

            p2 = p2->next;
            index2++;
        }

        if (carry > 0) {
            intermediate[index1 + index2] += carry;
        }

        p1 = p1->next;
        index1++;
    }

    // Find the first non-zero index in the intermediate array
    int product_length = num1.length + num2.length;
    int first_non_zero_index = product_length - 1;
    while (first_non_zero_index >= 0 && intermediate[first_non_zero_index] == 0) {
        first_non_zero_index--;
    }

    // Create the result struct based on the intermediate array
    for (int i = first_non_zero_index; i >= 0; i--) {
        addatfront(&(result.l), intermediate[i]);
        result.length++;
    }

    free(intermediate);
    struct node* ptr = result.l;
    ptr = reverse(ptr);
    result.l = ptr;
    return result;
}
// struct BigInteger div1(struct BigInteger A, struct BigInteger B)
// {
//     struct BigInteger C;
//     int l=length(B);
//     l--;
//     struct node*itr=A;
//     while(l)
//     {
//         int d=itr->data;
//         itr=itr->next;
//         (itr->data)=(itr->data)*10+d;
//         l--;
//     }
//     struct BigInteger Q=NULL;
//     int d=0;
//     while(itr)
//     {
//         struct BigInteger count=NULL;
//         while(itr->data)
//         {
//             if(compare(itr->data,B)>=0)
//             {
//                 break;
//             }
//             itr->data=sub(itr->data,B);
//             count++;
//         }
//         Q=Q*10+count;
//         d=itr->data;
//         itr=itr->next;
//         (itr->data)+=d*10;
//     }
//     return Q;
// }
// struct BigInteger div1(struct BigInteger A, struct BigInteger B) {
//     struct BigInteger C;
//     C.l = NULL;
//     C.length = 0;
//     C.sign = (A.sign == B.sign) ? 1 : -1; // Determine the sign of the result

//     if (compare(A, B) == -1) {
//         // If the dividend (A) is smaller than the divisor (B), the result is zero.
//         return C;
//     }

//     struct BigInteger Q;
//     Q.l = NULL;
//     Q.length = 0;
//     Q.sign = 1;

//     struct node* itr = A.l;
//     struct BigInteger temp;
//     temp.l = NULL;
//     temp.length = 0;
//     temp.sign = 1;

//     while (itr) {
//         // Bring down the next digit from the dividend
//         temp = createBigInteger(1, &(itr->data));
//         printf("Start\n");
//         display(Q);
//         // Keep adding digits until we have a number greater than or equal to the divisor
//         while (compare(temp, B) !=-1) {
//             itr = itr->next;
//             if (itr) {
//                 // temp=temp*10+itr->data;
//                 temp = mul(temp, createBigInteger(10, NULL));
//                 printf("Hello\n");
//                 display(temp);
//                 // temp.l=temp.l+itr->data;
//                 temp = add(temp, createBigInteger(1, &(itr->data)));
//             }
//         }
//         printf("mid\n");
//         display(Q);
//         temp=rev(temp);
//         // Find the largest digit for division
//         int digit = 0;
//         while (compare(temp, B) >=0) {
//             temp = sub(temp, B);
//             digit++;
//         }

//         // Append the digit to the quotient
//         Q = mul(Q, createBigInteger(10, NULL));
//         Q = add(Q, createBigInteger(1, &digit));
//         printf("end\n");
//         display(Q);
//         // Move to the next digit in the dividend
//         if (itr) {
//             itr = itr->next;
//         }
//     }

//     return Q;
// }
// struct BigInteger div1(struct BigInteger A, struct BigInteger B) {
//     struct BigInteger C;
//     C.l = NULL;
//     C.length = 0;
//     C.sign = (A.sign == B.sign) ? 1 : -1; // Determine the sign of the result

//     if (compare(A, B) == -1) {
//         // If the dividend (A) is smaller than the divisor (B), the result is zero.
//         return C;
//     }

//     struct BigInteger Q;
//     Q.l = NULL;
//     Q.length = 0;
//     Q.sign = 1;

//     struct node* itr = A.l;
//     struct BigInteger temp;
//     temp.l = NULL;
//     temp.length = 0;
//     temp.sign = 1;

//     while (itr) {
//         // Bring down the next digit from the dividend
//         temp = createBigInteger(1, &(itr->data));

//         // Keep adding digits until we have a number greater than or equal to the divisor
//         while (compare(temp, B) == -1) {
//             itr = itr->next;
//             if (itr) {
//                 temp = mul(temp, createBigInteger(10, NULL));
//                 temp = add(temp, createBigInteger(1, &(itr->data)));
//             }
//             else {
//                 // If there are no more digits to bring down, exit the loop
//                 break;
//             }
//         }

//         // Find the largest digit for division
//         int digit = 0;
//         while (compare(temp, B) >= 0) {
//             temp = sub(temp, B);
//             digit++;
//         }

//         // Append the digit to the quotient
//         Q = mul(Q, createBigInteger(1, &digit));

//         // Move to the next digit in the dividend
//         if (itr) {
//             itr = itr->next;
//         }
//     }

//     return Q;
// }
// struct BigInteger divideBy2(struct BigInteger num) {
//     struct BigInteger result;
//     result.l = NULL;
//     result.length = 0;
//     result.sign = num.sign;

//     int carry = 0;
//     struct node* current = num.l;

//     while (current) {
//         int value = current->data + carry * 10;
//         int quotient = value / 2;
//         carry = value % 2;
//         addatfront(&(result.l), quotient);
//         result.length++;
//         current = current->next;
//     }

//     // Remove leading zeros in the result
//     while (result.l && result.l->data == 0) {
//         struct node* temp = result.l;
//         result.l = result.l->next;
//         free(temp);
//         result.length--;
//     }

//     return result;
// }

struct BigInteger div1( struct BigInteger A,struct BigInteger B)
{
    struct BigInteger result;
    result.l=NULL;
    result.length=0;
    unsigned int count=0;
    if(A.sign==B.sign)
    {
        result.sign=1;
    }
    else
    {
        result.sign=-1;
    }
    A.sign=1;
    B.sign=1;
    struct BigInteger temp=B;
    while(compare(A,temp)>=0)
    {
        count++;
        temp= add(temp,B);
        
        temp.l=reverse(temp.l);
       
    }
    result.l=insert(count);
    return result;
}
struct node* insert(int n)
{
    struct node* list = NULL;

    int digit;

    do {
        digit = n % 10;
        addatfront((&list),digit);
        n = n / 10;
    } while(n > 0);
    return list;
}
// struct BigInteger div1(struct BigInteger b1, struct BigInteger b2)
// {
//     struct BigInteger quotient = initialize("0");
//     struct BigInteger one = initialize("1");
//     struct BigInteger null = initialize("");

//     int sign = (b1.sign == b2.sign) ? 1 : -1;
//     b1.sign = b2.sign = 1;
//     if (compare(b1, b2) == -1)
//     {
//         return quotient;
//     }
//     else if (compare(b1, b2) == 0)
//     {
//         one.sign = sign;
//         return one;
//     }
//     else if (b2.length == 1 && b2.l->data == 0)
//     {
//         return null;
//     }
//     else if (b2.length == 1 && b2.l->data == 1)
//     {
//         b1.sign = sign;
//         return b1;
//     }
//     quotient = add(quotient, one);
//     struct BigInteger dividend = b1;
//     struct BigInteger divisor = b2;
//     struct BigInteger multiple = divisor;
//     // Exponential Search ---->
//     while (compare(dividend, multiple) == 1 || compare(dividend, multiple) == 0)
//     {
//         multiple = add(multiple, multiple); // Exponentially increase the multiple
//         quotient = add(quotient, quotient); // Double the quotient
//     }
//     struct BigInteger result = initialize("0");
//     while (compare(dividend, divisor) == 1 || compare(dividend, divisor) == 0)
//     {
//         if (compare(dividend, multiple) == 1 || compare(dividend, multiple) == 0)
//         {
//             dividend = sub(dividend, multiple);
//             result = add(result, quotient);
//         }
//         multiple = divideBy2(multiple); // Divide the multiple by 2
//         quotient = divideBy2(quotient); // Divide the quotient by 2
//     }
//     result.sign = sign;
//     return result;
// }

struct BigInteger rev(struct BigInteger A)
{
    struct node *curr=A.l, *next = A.l, *prev=NULL;
    while(curr)
    {
        next=curr->next;
        curr->next=prev;
        prev=curr;
        curr=next;
    }
    A.l=prev;
    return A;
}
struct BigInteger length(struct BigInteger A)
{
    int p=0;
    struct node *temp=A.l;
    while(temp)
    {
        p++;
        temp=temp->next;
    }
    A.length=p;
    return A;
}
struct BigInteger createBigInteger(int length, int* digits) {
    struct BigInteger bigInt;
    bigInt.length = length;
    bigInt.l = NULL; // Initialize the linked list to NULL
    bigInt.sign = 1; // Assuming a positive value by default

    struct node* tail = NULL; // Keep track of the tail of the linked list

    for (int i = 0; i < length; i++) {
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        if (!newNode) {
            printf("Memory allocation failed\n");
            // You should add error handling here
            return bigInt; // Return an empty BigInteger if memory allocation fails
        }

        newNode->data = digits[i];
        newNode->next = NULL;

        if (bigInt.l == NULL) {
            // If the linked list is empty, set the head and tail to the new node
            bigInt.l = newNode;
            tail = newNode;
        } else {
            // Otherwise, add the new node at the end and update the tail
            tail->next = newNode;
            tail = newNode;
        }
    }

    return bigInt;
}
struct BigInteger mod(struct BigInteger A,struct BigInteger B)
{
    struct BigInteger result;
    result.l=NULL;
    result.length=0;
    unsigned int count=0;
    if(compare(A,B)==-1)
    {
        return rev(A);
    }
    if(A.sign==B.sign)
    {
        result.sign=1;
    }
    else
    {
        result.sign=-1;
    }
    
    A.sign=1;
    B.sign=1;
    struct BigInteger temp=B;
    struct BigInteger prev;
    while(compare(A,temp)>=0)
    {
        count++;
        prev=temp;
        temp= add(temp,B);
        temp.l=reverse(temp.l);
    }

    result=sub(A,prev);
    return result;
}
