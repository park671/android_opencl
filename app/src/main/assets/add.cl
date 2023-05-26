__kernel void add(__global int *srcBuffer,
                                    __global int *dstBuffer,
                                    const int size)
{
    int idx = get_global_id(0);
    if(idx < size) {
        dstBuffer[idx] = dstBuffer[idx] + srcBuffer[idx];
    }
}

