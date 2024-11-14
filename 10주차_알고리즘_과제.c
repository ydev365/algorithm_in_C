// https://www.acmicpc.net/problem/1202 에 대한 풀이

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight;
    int value;
} Jewel;

int compareJewel(const void *a, const void *b) {
    return ((Jewel *)a)->weight - ((Jewel *)b)->weight;
}

int compareBag(const void *a, const void *b) {
    return (*(int *)a) - (*(int *)b);
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);

    Jewel jewels[N];
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &jewels[i].weight, &jewels[i].value);
    }

    int bags[K];
    for (int i = 0; i < K; i++) {
        scanf("%d", &bags[i]);
    }

    // 보석과 가방을 각각 무게 기준으로 정렬
    qsort(jewels, N, sizeof(Jewel), compareJewel);
    qsort(bags, K, sizeof(int), compareBag);

    long long max_value = 0;
    int j = 0;

    // 최대 힙을 위한 우선순위 큐 생성
    int pq[N];
    int pq_size = 0;

    for (int i = 0; i < K; i++) {
        int bag_capacity = bags[i];

        // 현재 가방에 넣을 수 있는 모든 보석을 힙에 추가
        while (j < N && jewels[j].weight <= bag_capacity) {
            pq[pq_size++] = jewels[j++].value;
            int k = pq_size - 1;
            while (k > 0 && pq[(k - 1) / 2] < pq[k]) {
                int temp = pq[(k - 1) / 2];
                pq[(k - 1) / 2] = pq[k];
                pq[k] = temp;
                k = (k - 1) / 2;
            }
        }

        // 힙에서 가장 큰 가치를 가진 보석을 선택
        if (pq_size > 0) {
            max_value += pq[0];
            pq[0] = pq[--pq_size];
            int k = 0;
            while (k * 2 + 1 < pq_size) {
                int child = k * 2 + 1;
                if (child + 1 < pq_size && pq[child] < pq[child + 1]) child++;
                if (pq[k] >= pq[child]) break;
                int temp = pq[k];
                pq[k] = pq[child];
                pq[child] = temp;
                k = child;
            }
        }
    }

    printf("%lld\n", max_value);
    return 0;
}



// https://www.acmicpc.net/problem/4781 에 대한 풀이

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int calories;
    double price;
    double calorie_per_dollar;
} Candy;

int compare(const void *a, const void *b) {
    Candy *candyA = (Candy *)a;
    Candy *candyB = (Candy *)b;
    if (candyB->calorie_per_dollar > candyA->calorie_per_dollar) return 1;
    if (candyB->calorie_per_dollar < candyA->calorie_per_dollar) return -1;
    return 0;
}

int main() {
    while (1) {
        int n;
        double m;
        scanf("%d %lf", &n, &m);
        
        if (n == 0 && m == 0.00) break;

        Candy candies[n];
        for (int i = 0; i < n; i++) {
            int c;
            double p;
            scanf("%d %lf", &c, &p);
            candies[i].calories = c;
            candies[i].price = p;
            candies[i].calorie_per_dollar = c / p;
        }

        qsort(candies, n, sizeof(Candy), compare);

        int max_calories = 0;
        for (int i = 0; i < n; i++) {
            if (m >= candies[i].price) {
                int count = (int)(m / candies[i].price);
                max_calories += count * candies[i].calories;
                m -= count * candies[i].price;
            }
        }

        printf("%d\n", max_calories);
    }
    return 0;
}


// https://www.acmicpc.net/problem/1943 에 대한 풀이

#include <stdio.h>
#include <string.h>

#define MAX_N 100
#define MAX_SUM 100000

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int N;
        scanf("%d", &N);

        int coins[MAX_N], counts[MAX_N];
        int total_sum = 0;

        for (int i = 0; i < N; i++) {
            scanf("%d %d", &coins[i], &counts[i]);
            total_sum += coins[i] * counts[i];
        }

        if (total_sum % 2 != 0) {
            printf("0\n");
            continue;
        }

        int target = total_sum / 2;
        int dp[MAX_SUM + 1] = {0};
        dp[0] = 1;

        for (int i = 0; i < N; i++) {
            for (int j = target; j >= 0; j--) {
                if (dp[j]) {
                    for (int k = 1; k <= counts[i] && j + k * coins[i] <= target; k++) {
                        dp[j + k * coins[i]] = 1;
                    }
                }
            }
        }

        printf("%d\n", dp[target]);
    }

    return 0;
}





