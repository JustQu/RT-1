__kernel    void    main_kernel(__global uint *image)
{
    int global_id;
    int x;
    int y;

    global_id = get_global_id(0);
    x = global_id % 1200;
    y = global_id / 1200;
    image[global_id] = 0x00ff0000 + ((x % 255) << 8) + (y % 255);
    image[global_id] = ((int)(x * (255.0f / 1200)) << 8) + (y * (255.0f / 800));
}