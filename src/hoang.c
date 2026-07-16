#include "../include/restaurant.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* => KHAI BAO HAM IN MON AN (CUA PHAT) DE SU DUNG TRONG HOANG.C <= */
extern void inMonAn(MonAn mon);

/*==============================================================================
    CAC HAM HO TRO NOI BO CHO CAY BST (STATIC HELPER FUNCTIONS)
==============================================================================*/

/*
 * Cấp phát bộ nhớ RAM cho mot Node Cây (TreeNode) moi
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
 * Ghi thong tin 1 mon an ra file backup
 */
static void ghiMonAnRaFile(TreeNode* root, FILE* f)
{
    if (root != NULL && f != NULL)
    {
        fprintf(f, "%s,%s,%d\n", root->data.maMon, root->data.tenMon, root->data.giaTien);
    }
}

/*
 * Ham de quy ho tro ghi cay theo Pre-order ra file
 */
static void ghiCayPreorderHelper(TreeNode* root, FILE* f)
{
    if (root == NULL) return;
    ghiMonAnRaFile(root, f);
    ghiCayPreorderHelper(root->left, f);
    ghiCayPreorderHelper(root->right, f);
}

/*==============================================================================
    MODULE 3: CAY NHI PHAN TIM KIEM (PURE BST MODULE) - HOANG
    100% thao tac tren cau truc TreeNode, khong dung den Linked List!
==============================================================================*/

/*
 * 1. Them mot mon an vao cay BST theo Ma mon (De quy)
 * Quy tac: Ma nho hon di ben Trai, Ma lon hon di ben Phai
 * [BAY LOI]: Khong cho phep trung ma mon de dam bao cau truc BST chuan!
 */
TreeNode* themVaoCayBST(TreeNode* root, MonAn mon)
{
    if (root == NULL)
    {
        return taoTreeNode(mon);
    }

    int cmp = strcmp(mon.maMon, root->data.maMon);
    if (cmp < 0)
    {
        root->left = themVaoCayBST(root->left, mon);
    }
    else if (cmp > 0)
    {
        root->right = themVaoCayBST(root->right, mon);
    }
    // Neu cmp == 0 (Trung ma mon), tu dong bo qua, khong tao Node rac tren cay!
    return root;
}

/*
 * 2. Tim kiem mon an tren cay BST theo MA MON
 * Tốc độ xử lý: O(log n) nhờ tận dụng cờ định hướng Left/Right
 */
TreeNode* timKiemTheoMaBST(TreeNode* root, char* maMon)
{
    if (root == NULL || strcmp(root->data.maMon, maMon) == 0)
    {
        return root;
    }

    if (strcmp(maMon, root->data.maMon) < 0)
    {
        return timKiemTheoMaBST(root->left, maMon);
    }
    else
    {
        return timKiemTheoMaBST(root->right, maMon);
    }
}

/*
 * 3. Duyet cay theo Pre-order (NLR: Goc -> Trai -> Phai)
 * Ung dung: In cau truc phan nhanh Goc cua thuc don
 */
void duyetCayPreorder(TreeNode* root)
{
    if (root == NULL) return;
    inMonAn(root->data);
    duyetCayPreorder(root->left);
    duyetCayPreorder(root->right);
}

/*
 * 4. Duyet cay theo In-order (LNR: Trai -> Goc -> Phai)
 * Ung dung: TU DONG IN THUC DON SAP XEP TANG DAN A-Z theo Ma mon!
 * (Nho tinh chat BST, thuc don tu dong duoc sort ma khong can thuat toan sap xep)
 */
void duyetCayInorder(TreeNode* root)
{
    if (root == NULL) return;
    duyetCayInorder(root->left);
    inMonAn(root->data);
    duyetCayInorder(root->right);
}

/*
 * 5. Duyet cay theo Post-order (LRN: Trai -> Phai -> Goc)
 * Ung dung: Quet tu la len goc (Ho tro co che don dep RAM)
 */
void duyetCayPostorder(TreeNode* root)
{
    if (root == NULL) return;
    duyetCayPostorder(root->left);
    duyetCayPostorder(root->right);
    inMonAn(root->data);
}

/*
 * 6. Giai phong bo nho RAM cho cay BST (Duyet Post-order tu la len goc)
 * Tieu huy Node con truoc khi xoa Node cha -> Dam bao 0% Memory Leak!
 */
void giaiPhongCay(TreeNode* root)
{
    if (root == NULL) return;
    giaiPhongCay(root->left);
    giaiPhongCay(root->right);
    free(root);
}

/*
 * 7. Sao luu cau truc cay BST ra file Backup bang chuoi Pre-order
 * Giup khi read file nap lai vao RAM, cay khong bi mat dang can bang cu
 */
void saoLuuCayBST(TreeNode* root, const char* tenFile)
{
    FILE* f = fopen(tenFile, "w");
    if (f == NULL)
    {
        printf("[LOI] Khong the tao file backup %s!\n", tenFile);
        return;
    }
    ghiCayPreorderHelper(root, f);
    fclose(f);
    printf("=> Da sao luu cau truc cay BST ra file [%s] theo chuoi Pre-order!\n", tenFile);
}