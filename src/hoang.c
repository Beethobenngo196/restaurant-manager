#include "restaurant.h"

/*=========================================================
    CAC HAM NOI BO (STATIC HELPER FUNCTIONS)
=========================================================*/

/*
 * Tao mot TreeNode moi
 */
static TreeNode* taoTreeNode(MonAn mon)
{
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));

    if (node == NULL)
    {
        return NULL;
    }

    node->data = mon;
    node->left = NULL;
    node->right = NULL;

    return node;
}

/*
 * Hoan doi du lieu cua hai node Linked List
 */
static void hoanDoiMonAn(Node* a, Node* b)
{
    MonAn temp = a->data;
    a->data = b->data;
    b->data = temp;
}

/*
 * In tieu de bang
 */
static void inTieuDeBang(void)
{
    printf("%-10s %-30s %-10s\n",
           "Ma Mon",
           "Ten Mon",
           "Gia");
}

/*
 * In mot mon an
 */
static void inMonAn(MonAn mon)
{
    printf("%-10s %-30s %-10d\n",
           mon.maMon,
           mon.tenMon,
           mon.giaTien);
}

/*=========================================================
    BINARY SEARCH TREE (BST) MODULE
=========================================================*/

/*
 * Them mot mon vao cay BST
 */
TreeNode* themVaoCayBST(TreeNode* root, MonAn mon)
{
    if (root == NULL)
    {
        return taoTreeNode(mon);
    }

    if (strcmp(mon.maMon, root->data.maMon) < 0)
    {
        root->left = themVaoCayBST(root->left, mon);
    }
    else
    {
        root->right = themVaoCayBST(root->right, mon);
    }

    return root;
}

/*
 * Tim kiem theo ma mon
 */
TreeNode* timKiemTheoMaBST(TreeNode* root, char* maMon)
{
    if (root == NULL)
    {
        return NULL;
    }

    int cmp = strcmp(maMon, root->data.maMon);

    if (cmp == 0)
    {
        return root;
    }

    if (cmp < 0)
    {
        return timKiemTheoMaBST(root->left, maMon);
    }

    return timKiemTheoMaBST(root->right, maMon);
}

/*
 * Duyet cay theo Preorder (NLR)
 */
void duyetCayPreorder(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }

    inMonAn(root->data);

    duyetCayPreorder(root->left);
    duyetCayPreorder(root->right);
}

/*
 * Duyet cay theo Inorder (LNR)
 */
void duyetCayInorder(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }

    duyetCayInorder(root->left);

    inMonAn(root->data);

    duyetCayInorder(root->right);
}

/*
 * Duyet cay theo Postorder (LRN)
 */
void duyetCayPostorder(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }

    duyetCayPostorder(root->left);
    duyetCayPostorder(root->right);

    inMonAn(root->data);
}

/*
 * Giai phong bo nho BST
 */
void giaiPhongCay(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }

    giaiPhongCay(root->left);
    giaiPhongCay(root->right);

    free(root);
}

/*=========================================================
    SEARCH MODULE (LINKED LIST)
=========================================================*/

/*
 * Tim kiem theo ten mon
 */
void timKiemTheoTen(Node* head, char* tenMon)
{
    if (head == NULL)
    {
        printf("Danh sach rong.\n");
        return;
    }

    Node* p = head;
    int timThay = 0;

    printf("\n========== KET QUA TIM KIEM ==========\n");

    while (p != NULL)
    {
        if (strcmp(p->data.tenMon, tenMon) == 0)
        {
            if (!timThay)
            {
                inTieuDeBang();
            }

            inMonAn(p->data);
            timThay = 1;
        }

        p = p->next;
    }

    if (!timThay)
    {
        printf("Khong tim thay mon \"%s\".\n", tenMon);
    }
}

/*
 * Tim kiem theo khoang gia
 */
void timKiemTheoKhoangGia(Node* head, int giaMin, int giaMax)
{
    if (head == NULL)
    {
        printf("Danh sach rong.\n");
        return;
    }

    Node* p = head;
    int timThay = 0;

    if (giaMin > giaMax)
    {
        int temp = giaMin;
        giaMin = giaMax;
        giaMax = temp;
    }

    printf("\n======= KET QUA TIM KIEM THEO GIA =======\n");

    while (p != NULL)
    {
        if (p->data.giaTien >= giaMin && p->data.giaTien <= giaMax)
        {
            if (!timThay)
            {
                inTieuDeBang();
            }

            inMonAn(p->data);
            timThay = 1;
        }

        p = p->next;
    }

    if (!timThay)
    {
        printf("Khong co mon nao trong khoang gia %d - %d.\n",
               giaMin,
               giaMax);
    }
}

/*=========================================================
    SORT MODULE (LINKED LIST)
=========================================================*/

/*
 * Sap xep theo ten
 * tangDan = 1 : A -> Z
 * tangDan = 0 : Z -> A
 */
void sapXepTheoTen(Node** head, int tangDan)
{
    if (head == NULL || *head == NULL || (*head)->next == NULL)
    {
        return;
    }

    Node* p;
    Node* q;

    for (p = *head; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            int cmp = strcmp(p->data.tenMon, q->data.tenMon);

            if ((tangDan && cmp > 0) || (!tangDan && cmp < 0))
            {
                hoanDoiMonAn(p, q);
            }
        }
    }
}

/*
 * Sap xep theo ma
 * tangDan = 1 : Tang dan
 * tangDan = 0 : Giam dan
 */
void sapXepTheoMa(Node** head, int tangDan)
{
    if (head == NULL || *head == NULL || (*head)->next == NULL)
    {
        return;
    }

    Node* p;
    Node* q;

    for (p = *head; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            int cmp = strcmp(p->data.maMon, q->data.maMon);

            if ((tangDan && cmp > 0) || (!tangDan && cmp < 0))
            {
                hoanDoiMonAn(p, q);
            }
        }
    }
}

/*
 * Sap xep theo gia
 * tangDan = 1 : Gia thap -> cao
 * tangDan = 0 : Gia cao -> thap
 */
void sapXepTangTheoGia(Node** head, int tangDan)
{
    if (head == NULL || *head == NULL || (*head)->next == NULL)
    {
        return;
    }

    Node* p;
    Node* q;

    for (p = *head; p != NULL; p = p->next)
    {
        for (q = p->next; q != NULL; q = q->next)
        {
            if ((tangDan && p->data.giaTien > q->data.giaTien) ||
                (!tangDan && p->data.giaTien < q->data.giaTien))
            {
                hoanDoiMonAn(p, q);
            }
        }
    }
}