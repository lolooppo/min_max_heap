# min_max_heap
This is a new data structure which returns the max or the min in just o(1).

# Description:
On a binary heap with N items, you end up with log_2 N layers and have to do up to log_2 N comparisons. In an interval heap you’re using two heaps internally, so each heap ends up with log_2 (N/2)=(log_2 N)-1 layers. So it’s only removing one layer in exchange for doing more work per layer. In a min-max heap we can skip every other layer, so we only have to do (log_2 N)/2 comparisons. That’s a big difference. As an example, log_2(1000)=log_2(1000000)/2. Meaning if if this was the only number that counted, a min-max heap of size 1,000,000 would be as fast as a binary heap of size 1,000.

Here are pictures from [wikipedia](https://en.wikipedia.org/wiki/Min-max_heap) 

![Min-max_heap](https://github.com/lolooppo/min_max_heap/assets/99070234/8f48d4ae-e24d-4e60-b6eb-7c575ea33690)

![push_minmax_heap](https://github.com/lolooppo/min_max_heap/assets/99070234/9eb00253-6bed-406e-b59c-0e5c3ea2ae9e)

![pop_minmax_heap-1](https://github.com/lolooppo/min_max_heap/assets/99070234/c6129947-172d-47eb-bb97-980fae60239a)

![make_minmax_heap](https://github.com/lolooppo/min_max_heap/assets/99070234/f8d480c3-b032-481c-bcd0-ac377073184f)

Useful read [here](https://probablydance.com/2020/08/31/on-modern-hardware-the-min-max-heap-beats-a-binary-heap/).
