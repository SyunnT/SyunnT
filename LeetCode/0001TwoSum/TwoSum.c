/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>

/* **********************
** 算法区域
********************** */
// 方法控制宏
#define METHOD 2

// 双循环遍历
#if METHOD == 1
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    *returnSize = 0;
    int a = 0, b = 0;
    for (int i = 0; i < numsSize; ++i) {
        for (int j = i + 1; j < numsSize; ++j) {
            if (nums[i] + nums[j] == target) {
                a = i;
                b = j;
                *returnSize = 2;
                int* result = malloc(sizeof(int) * 2);
                result[0] = a;
                result[1] = b;
                return result;
            }
        }
    }
    return NULL;
}

// 哈希表实现
#elif METHOD == 2
// 1. 节点类型
typedef struct recordtype
{
    struct recordtype* next;
    int key;
    int value;
} RecordType;
void setRecord(RecordType* record, int key, int value)
{
    record->key = key;
    record->value = value;
}
int getKey(const RecordType* record)
{
    return record->key;
}
int getValue(const RecordType* record)
{
    return record->value;
}

// 2. 哈希表
typedef struct
{
    RecordType* records;
    int size;
    int length;
} HashTable;
/// @return 0 失败；1 成功
int initHashTable(HashTable* table, int size)
{
    table->length = 0;
    table->records = NULL;
    table->size = size;
    table->records = (RecordType*)calloc(size, sizeof(RecordType));
    if(!table->records) {
        return 0;
    }
    return 1;
}
void destroyTable(HashTable* table)
{
    if(table->records) {
        free(table->records);
    }
}
int hashAlgo(int key);

// int* twoSum(int* nums, int numsSize, int target, int* returnSize)
// {

// }

#endif

/* **********************
** 辅助函数区域
********************** */
// 打印结果
void printResult(const int* nums, int numsSize, int target, const int* ret, int retSize)
{
    printf("输入：nums = [");
    for (int i = 0; i < numsSize; ++i) {
        if (i) {
            printf(",");
        }
        printf("%d", nums[i]);
    }
    printf("]");
    printf(", target = %d\n", target);
    printf("输出：");
    if (retSize == 0) {
        printf("NULL");
    }
    else {
        printf("[");
        for (int i = 0; i < retSize; ++i) {
            if (i) {
                printf(",");
            }
            printf("%d", ret[i]);
        }
        printf("]");
    }
    printf("\n");
}

/* **********************
** 测试程序
********************** */
int main()
{
    // int nums1[4] = {2, 7, 11, 15};
    // int target1 = 9;
    // int returnSize1 = 0;
    // int* result1 = twoSum(nums1, 4, target1, &returnSize1);

    // int nums2[3] = {3, 2, 4};
    // int target2 = 6;
    // int returnSize2 = 0;
    // int* result2 = twoSum(nums2, 3, target2, &returnSize2);

    // int nums3[2] = {3, 3};
    // int target3 = 6;
    // int returnSize3 = 0;
    // int* result3 = twoSum(nums3, 2, target3, &returnSize3);

    // printResult(nums1, 4, target1, result1, returnSize1);
    // printResult(nums2, 3, target2, result2, returnSize2);
    // printResult(nums3, 2, target3, result3, returnSize3);
    // if (result1) free(result1);
    // if (result2) free(result2);
    // if (result3) free(result3);

    return 0;
}
