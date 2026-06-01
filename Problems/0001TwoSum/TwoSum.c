/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
#include <stdio.h>
#include <stdlib.h>

/// @brief 方法控制宏
#define METHOD 2

#if METHOD == 1
/// @brief 双循环遍历
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

#elif METHOD == 2

typedef struct hashmapnode
{
    int key;
    int value;
} HashMapNode;
void InitNode(HashMapNode* node, int key, int value)
{
    node->key = key;
    node->value = value;
}

typedef struct hashmap
{
    HashMapNode* nodes;
    int size;
    int capacity;
} HashMap;
HashMap* InitHashMap(int capacity)
{
    HashMap* map = malloc(sizeof(HashMap));
    if (!map) {
        return NULL;
    }
    map->nodes = malloc(sizeof(HashMapNode) * capacity);
    if (!map->nodes) {
        free(map);
        return NULL;
    }
    map->size = 0;
    map->capacity = capacity;
}
void DeleteHashMap(HashMap* map)
{
    if (!map) {
        return;
    }
    free(map->nodes);
    free(map);
}
int Hash(int key, int capacity)
{
    return key % capacity;
}
int Contains(HashMap* map, int key)
{}
int GetValue(HashMap* map, int key);
int AddNode(HashMap* map, int key, int value);

/// @brief 哈希表
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    *returnSize = 0;
    HashMap* map = InitHashMap(numsSize);
    if (!map) {
        printf("InitHashMap failed\n");
        return NULL;
    }
    for (int i = 0; i < numsSize; ++i) {
        int other = target - nums[i];
        if (Contains(map, other)) {
            int* result = malloc(sizeof(int) * 2);
            result[0] = GetValue(map, other);
            result[1] = i;
            *returnSize = 2;
            DeleteHashMap(map);
            return result;
        }
        if (Contains(map, nums[i]) == 0) {
            AddNode(map, nums[i], i);
        }
    }
    DeleteHashMap(map);
    return NULL;
}

#endif

/// @brief 打印结果
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
