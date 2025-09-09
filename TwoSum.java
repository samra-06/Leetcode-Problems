class Solution {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> map = new HashMap<>(); // value -> index

        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            
            if (map.containsKey(complement)) {
                // Found the pair
                return new int[] { map.get(complement), i };
            }
            
            map.put(nums[i], i);
        }
        
        // Problem guarantees one solution, but to satisfy compiler:
        return new int[] {};
    }
}