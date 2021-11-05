#include <stdio.h>
#include <stdlib.h>

enum nodeColor
{
    Red,
    Black,
};

struct ourRedBlackTreeNode
{
    int data, color;
    struct ourRedBlackTreeNode *children[2];
    //index-0 for left
    //index-1 for right
} *root = NULL;

struct ourRedBlackTreeNode *createNode(int data)
{
    struct ourRedBlackTreeNode *newnode;
    newnode = (struct ourRedBlackTreeNode *)malloc(sizeof(struct ourRedBlackTreeNode));
    newnode->data = data;
    newnode->color = Red;
    newnode->children[0] = newnode->children[1] = NULL;
    return newnode;
}

void insertion(int data)
{
    struct ourRedBlackTreeNode *stack[100], *ptr, *newnode, *xPtr, *yPtr;
    int direction[100], ht = 0, index;
    ptr = root;
    if (!root)
    {
        root = createNode(data);
        return;
    }

    stack[ht] = root;
    direction[ht++] = 0;
    while (ptr != NULL)
    {
        if (ptr->data == data)
        {
            printf("Already present!!\n");
            return;
        }
        index = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        ptr = ptr->children[index];
        direction[ht++] = index;
    }
    stack[ht - 1]->children[index] = newnode = createNode(data);
    while ((ht >= 3) && (stack[ht - 1]->color == Red))
    {
        if (direction[ht - 2] == 0)
        {
            yPtr = stack[ht - 2]->children[1];
            if (yPtr != NULL && yPtr->color == Red)
            {
                stack[ht - 2]->color = Red;
                stack[ht - 1]->color = yPtr->color = Black;
                ht = ht - 2;
            }
            else
            {
                if (direction[ht - 1] == 0)
                {
                    yPtr = stack[ht - 1];
                }
                else
                {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->children[1];
                    xPtr->children[1] = yPtr->children[0];
                    yPtr->children[0] = xPtr;
                    stack[ht - 2]->children[0] = yPtr;
                }
                xPtr = stack[ht - 2];
                xPtr->color = Red;
                yPtr->color = Black;
                xPtr->children[0] = yPtr->children[1];
                yPtr->children[1] = xPtr;
                if (xPtr == root)
                {
                    root = yPtr;
                }
                else
                {
                    stack[ht - 3]->children[direction[ht - 3]] = yPtr;
                }
                break;
            }
        }
        else
        {
            yPtr = stack[ht - 2]->children[0];
            if ((yPtr != NULL) && (yPtr->color == Red))
            {
                stack[ht - 2]->color = Red;
                stack[ht - 1]->color = yPtr->color = Black;
                ht = ht - 2;
            }
            else
            {
                if (direction[ht - 1] == 1)
                {
                    yPtr = stack[ht - 1];
                }
                else
                {
                    xPtr = stack[ht - 1];
                    yPtr = xPtr->children[0];
                    xPtr->children[0] = yPtr->children[1];
                    yPtr->children[1] = xPtr;
                    stack[ht - 2]->children[1] = yPtr;
                }
                xPtr = stack[ht - 2];
                yPtr->color = Black;
                xPtr->color = Red;
                xPtr->children[1] = yPtr->children[0];
                yPtr->children[0] = xPtr;
                if (xPtr == root)
                {
                    root = yPtr;
                }
                else
                {
                    stack[ht - 3]->children[direction[ht - 3]] = yPtr;
                }
                break;
            }
        }
    }
    root->color = Black;
}

void deletion(int data)
{
    struct ourRedBlackTreeNode *stack[100], *ptr, *xPtr, *yPtr;
    struct ourRedBlackTreeNode *pPtr, *qPtr, *rPtr;
    int direction[100], ht = 0, diff, i;
    enum nodeColor color;

    if (!root)
    {
        printf("Tree not available\n");
        return;
    }

    ptr = root;
    while (ptr != NULL)
    {
        if ((data - ptr->data) == 0)
            break;
        diff = (data - ptr->data) > 0 ? 1 : 0;
        stack[ht] = ptr;
        direction[ht++] = diff;
        ptr = ptr->children[diff];
    }

    if (ptr->children[1] == NULL)
    {
        if ((ptr == root) && (ptr->children[0] == NULL))
        {
            free(ptr);
            root = NULL;
        }
        else if (ptr == root)
        {
            root = ptr->children[0];
            free(ptr);
        }
        else
        {
            stack[ht - 1]->children[direction[ht - 1]] = ptr->children[0];
        }
    }
    else
    {
        xPtr = ptr->children[1];
        if (xPtr->children[0] == NULL)
        {
            xPtr->children[0] = ptr->children[0];
            color = xPtr->color;
            xPtr->color = ptr->color;
            ptr->color = color;

            if (ptr == root)
            {
                root = xPtr;
            }
            else
            {
                stack[ht - 1]->children[direction[ht - 1]] = xPtr;
            }

            direction[ht] = 1;
            stack[ht++] = xPtr;
        }
        else
        {
            i = ht++;
            while (1)
            {
                direction[ht] = 0;
                stack[ht++] = xPtr;
                yPtr = xPtr->children[0];
                if (!yPtr->children[0])
                    break;
                xPtr = yPtr;
            }

            direction[i] = 1;
            stack[i] = yPtr;
            if (i > 0)
                stack[i - 1]->children[direction[i - 1]] = yPtr;

            yPtr->children[0] = ptr->children[0];

            xPtr->children[0] = yPtr->children[1];
            yPtr->children[1] = ptr->children[1];

            if (ptr == root)
            {
                root = yPtr;
            }

            color = yPtr->color;
            yPtr->color = ptr->color;
            ptr->color = color;
        }
    }

    if (ht < 1)
        return;

    if (ptr->color == Black)
    {
        while (1)
        {
            pPtr = stack[ht - 1]->children[direction[ht - 1]];
            if (pPtr && pPtr->color == Red)
            {
                pPtr->color = Black;
                break;
            }

            if (ht < 2)
                break;

            if (direction[ht - 2] == 0)
            {
                rPtr = stack[ht - 1]->children[1];

                if (!rPtr)
                    break;

                if (rPtr->color == Red)
                {
                    stack[ht - 1]->color = Red;
                    rPtr->color = Black;
                    stack[ht - 1]->children[1] = rPtr->children[0];
                    rPtr->children[0] = stack[ht - 1];

                    if (stack[ht - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        stack[ht - 2]->children[direction[ht - 2]] = rPtr;
                    }
                    direction[ht] = 0;
                    stack[ht] = stack[ht - 1];
                    stack[ht - 1] = rPtr;
                    ht++;

                    rPtr = stack[ht - 1]->children[1];
                }

                if ((!rPtr->children[0] || rPtr->children[0]->color == Black) &&
                    (!rPtr->children[1] || rPtr->children[1]->color == Black))
                {
                    rPtr->color = Red;
                }
                else
                {
                    if (!rPtr->children[1] || rPtr->children[1]->color == Black)
                    {
                        qPtr = rPtr->children[0];
                        rPtr->color = Red;
                        qPtr->color = Black;
                        rPtr->children[0] = qPtr->children[1];
                        qPtr->children[1] = rPtr;
                        rPtr = stack[ht - 1]->children[1] = qPtr;
                    }
                    rPtr->color = stack[ht - 1]->color;
                    stack[ht - 1]->color = Black;
                    rPtr->children[1]->color = Black;
                    stack[ht - 1]->children[1] = rPtr->children[0];
                    rPtr->children[0] = stack[ht - 1];
                    if (stack[ht - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        stack[ht - 2]->children[direction[ht - 2]] = rPtr;
                    }
                    break;
                }
            }
            else
            {
                rPtr = stack[ht - 1]->children[0];
                if (!rPtr)
                    break;

                if (rPtr->color == Red)
                {
                    stack[ht - 1]->color = Red;
                    rPtr->color = Black;
                    stack[ht - 1]->children[0] = rPtr->children[1];
                    rPtr->children[1] = stack[ht - 1];

                    if (stack[ht - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        stack[ht - 2]->children[direction[ht - 2]] = rPtr;
                    }
                    direction[ht] = 1;
                    stack[ht] = stack[ht - 1];
                    stack[ht - 1] = rPtr;
                    ht++;

                    rPtr = stack[ht - 1]->children[0];
                }
                if ((!rPtr->children[0] || rPtr->children[0]->color == Black) &&
                    (!rPtr->children[1] || rPtr->children[1]->color == Black))
                {
                    rPtr->color = Red;
                }
                else
                {
                    if (!rPtr->children[0] || rPtr->children[0]->color == Black)
                    {
                        qPtr = rPtr->children[1];
                        rPtr->color = Red;
                        qPtr->color = Black;
                        rPtr->children[1] = qPtr->children[0];
                        qPtr->children[0] = rPtr;
                        rPtr = stack[ht - 1]->children[0] = qPtr;
                    }
                    rPtr->color = stack[ht - 1]->color;
                    stack[ht - 1]->color = Black;
                    rPtr->children[0]->color = Black;
                    stack[ht - 1]->children[0] = rPtr->children[1];
                    rPtr->children[1] = stack[ht - 1];
                    if (stack[ht - 1] == root)
                    {
                        root = rPtr;
                    }
                    else
                    {
                        stack[ht - 2]->children[direction[ht - 2]] = rPtr;
                    }
                    break;
                }
            }
            ht--;
        }
    }
}

void inorderTraversal(struct ourRedBlackTreeNode *node)
{
    if (node)
    {
        inorderTraversal(node->children[0]);
        printf("%d  ", node->data);
        inorderTraversal(node->children[1]);
    }
    return;
}

int main()
{
    int ch, data;
    while (1)
    {
        printf("1. Insertion\t2. Deletion\n");
        printf("3. Traverse\t4. Exit");
        printf("\nEnter your choice:");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:
            printf("Enter the element to insert:");
            scanf("%d", &data);
            insertion(data);
            break;
        case 2:
            printf("Enter the element to delete:");
            scanf("%d", &data);
            deletion(data);
            break;
        case 3:
            inorderTraversal(root);
            printf("\n");
            break;
        case 4:
            exit(0);
        default:
            printf("Not available\n");
            break;
        }
        printf("\n");
    }
    return 0;
}