# min_max_heap
This is a new data structure which returns the max or the min in just o(1).

# Description:
On a binary heap with N items, you end up with log_2 N layers and have to do up to log_2 N comparisons. In an interval heap you’re using two heaps internally, so each heap ends up with log_2 (N/2)=(log_2 N)-1 layers. So it’s only removing one layer in exchange for doing more work per layer. In a min-max heap we can skip every other layer, so we only have to do (log_2 N)/2 comparisons. That’s a big difference. As an example, log_2(1000)=log_2(1000000)/2. Meaning if if this was the only number that counted, a min-max heap of size 1,000,000 would be as fast as a binary heap of size 1,000.

## Useful pictures from [WIKIPEDIA]([https://website-name.com](https://probablydance.com/2020/08/31/on-modern-hardware-the-min-max-heap-beats-a-binary-heap/)https://probablydance.com/2020/08/31/on-modern-hardware-the-min-max-heap-beats-a-binary-heap/)

