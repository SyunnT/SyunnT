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
    RecordType** records;
    uint32_t size;
    uint32_t length;
} HashTable;
/// @return 0 失败；1 成功
int initHashTable(HashTable* table, uint32_t size)
{
    table->length = 0;
    table->records = NULL;
    table->size = size;
    // 全部初始化为 NULL
    table->records = (RecordType**)calloc(size, sizeof(RecordType*));
    if (!table->records) {
        return 0;
    }
    return 1;
}
void destroyTable(HashTable* table)
{
    RecordType** records = table->records;
    // 删除所有节点
    for (int i = 0; i < table->size; ++i) {
        RecordType* record = records[i];
        if (!record) {
            continue;
        }
        RecordType* del = record;
        while(record) {
            del = record;
            record = del->next;
            free(del);
        }
        records[i] = NULL;
    }
    // 删除数组
    free(records);
    table->records = NULL;
}
uint32_t hashAlgo(const HashTable* table, int key)
{
    uint32_t x = (uint32_t)key;

    x ^= x >> 16;
    x *= 0x85ebca6b;
    x ^= x >> 13;
    x *= 0xc2b2ae35;
    x ^= x >> 16;

    return x % table->size;
}
/// @return 0 成功；-1 内存分配失败
int tableInsert(HashTable* table, int key, int value)
{
    uint32_t index = hashAlgo(table, key);
    RecordType* record = (RecordType*)malloc(sizeof(RecordType));
    if(!record) return -1;
    record->key = key;
    record->value = value;
    record->next = table->records[index];
    table->records[index] = record;
    ++table->length;
    return 0;
}
/// @return 0 找到；1 未找到
/// @param value 做值返回
int tableFind(const HashTable* table, int key, int* value)
{
    uint32_t index = hashAlgo(table, key);
    RecordType* record = table->records[index];
    while (record) {
        if (record->key == key) {
            *value = record->value;
            return 0;
        }
        record = record->next;
    }
    return 1;
}

int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    HashTable table;
    int ret = initHashTable(&table, numsSize);
    if (ret != 1) goto end_without_malloc;
    int j = -1;
    for (int i = 0; i < numsSize; ++i) {
        if (!tableFind(&table, target-nums[i], &j)) {
            int* result = (int*)malloc(sizeof(int) * 2);
            if(!result) goto end;
            result[0] = j;
            result[1] = i;
            *returnSize = 2;
            return result;
        }
        if(tableInsert(&table, nums[i], i) == -1) goto end;
    }

end:
    destroyTable(&table);
end_without_malloc:
    *returnSize = 0;
    return NULL;
}

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
    int nums1[4] = {2, 7, 11, 15};
    int target1 = 9;
    int returnSize1 = 0;
    int* result1 = twoSum(nums1, 4, target1, &returnSize1);

    int nums2[3] = {3, 2, 4};
    int target2 = 6;
    int returnSize2 = 0;
    int* result2 = twoSum(nums2, 3, target2, &returnSize2);

    int nums3[2] = {3, 3};
    int target3 = 6;
    int returnSize3 = 0;
    int* result3 = twoSum(nums3, 2, target3, &returnSize3);

    printResult(nums1, 4, target1, result1, returnSize1);
    printResult(nums2, 3, target2, result2, returnSize2);
    printResult(nums3, 2, target3, result3, returnSize3);
    if (result1) free(result1);
    if (result2) free(result2);
    if (result3) free(result3);

    return 0;
}
