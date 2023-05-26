__kernel void same(__global int *srcBuffer,
                                    __global int *dstBuffer,
                                    __global int *result,
                                    const int size)
{
    int idx = get_global_id(0);
    if(idx < size && result[0] == 0 && dstBuffer[idx] != srcBuffer[idx]) {
        result[0] = 1;
    }
}

