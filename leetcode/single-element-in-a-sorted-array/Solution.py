class Solution(object):
    def singleNonDuplicate(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        l = 0
        r = len(nums)-1

        while l <= r:
            mid = l + (r-l)/2

            if ( mid-1<0 or nums[mid] != nums[mid-1]) and (mid+1>=len(nums) or nums[mid] != nums[mid+1]):
                return nums[mid]

            if (mid+1 <= r and nums[mid] == nums[mid+1]):
                rstart = mid+2
            elif (mid-1>=l and nums[mid] == nums[mid-1]):
                rstart = mid+1

            if (r-rstart+1)%2 == 1:
                l=rstart
            else:
                r=rstart-3

#nums = [1,1,2,2,4,4,5,5,9]
nums = [0,1,1,2,2,5,5]

print Solution().singleNonDuplicate(nums)
