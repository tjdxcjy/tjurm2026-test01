#include "tests.h"

// 练习1，实现库函数strlen
int my_strlen(char *str) {
    /**
     * 统计字符串的长度。
     */

    // IMPLEMENT YOUR CODE HERE
     int length = 0;
    
    while (*str != '\0') {
        
        length++;
        
        str++;
    }
    return length;
}
    


// 练习2，实现库函数strcat
void my_strcat(char *str_1, char *str_2) {
    /**
     * 将字符串str_2拼接到str_1之后，我们保证str_1指向的内存空间足够用于添加str_2。
     * 注意结束符'\0'的处理。
     */

    // IMPLEMENT YOUR CODE HERE
     while (*str_1 != '\0') {
        str_1++;
    }
    
    while (*str_2 != '\0') {
        *str_1 = *str_2;
        str_1++;
        str_2++;
    }
    
    *str_1 = '\0';

}


// 练习3，实现库函数strstr
char* my_strstr(char *s, char *p) {
    /**
     * 在字符串s中搜索字符串p，如果存在就返回第一次找到的地址，不存在就返回空指针(0)。
     * 例如：
     * s = "123456", p = "34"，应该返回指向字符'3'的指针。
     */

    // IMPLEMENT YOUR CODE HERE
    if (s == 0 || p == 0) return 0;
    if (*p == '\0') return s;  
    
    char *start, *pattern, *current;
    
    for (start = s; *start != '\0'; start++) {
        current = start;
        pattern = p;
        
        
        while (*pattern != '\0' && *current != '\0' && *current == *pattern) {
            current++;
            pattern++;
        }
        
        
        if (*pattern == '\0') {
            return start;
        }
        
       
        if (*current == '\0') {
            break;
        }
    }
    
    return 0;  
}

/**
 * ================================= 背景知识 ==================================
 * 1. 什么是图片？
 *    图片可以看做是由像素组成的一个方阵，图片分成两种，一种是灰度图片，颜色只有黑白
 * 两种，一种是彩色图片。
 *    灰度图片的每一个像素是一个范围在[0, 255]内的数值，数值越高就越接近白色。
 *    彩色图片的每一个像素都是一个长度为3的数组，数组中的每一个元素都是[0, 255]内的
 * 数值，3个数的含义分别是Red, Green, Blue，表示这个像素所在的位置这3种颜色的强度，
 * 举个例子，纯红色对应的像素就是{255, 0, 0}。这3个数称为图片的3个通道，这种像素表示
 * 方式也称之为图片的RGB表示方式。
 *
 * 2. 图片的属性？
 *    图片是一个方阵，所以具有宽、高两个属性，除此之外还有一个通道数，比如说灰度图片
 * 的通道数为1，RGB彩色图片的通道数为3。图片的宽高也称为图片的分辨率。
 *
 * 3. 图片在计算机中如何存储？
 *   灰度图片可以看成是二维数组，为方便计算，数据类型使用float。举个例子：
 *   float a[2][3] = {
 *      {121, 231, 35},
 *      {47, 52, 63}
 *   };
 *   就可以看做是一个高为2，宽为3的灰度图片。实际上图片的宽高都比较大，比如说500。
 *
 *   彩色图片也可以看作是由像素构成的二维数组，举个例子，一张高为2，宽为3彩色图片在
 * 内存中的存储为：
 *
 *   低地址 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - >>> 高地址
 *
 *    R    G    B    R    G    B    R    G    B    R    G    B    R    G    B    R    G    B
 *   111, 123, 215, 233, 123, 142, 156, 233, 267, 223, 234, 175, 123, 117, 168, 123, 156, 156
 *   |< -------- >| |< -------- >| |< -------- >| |< -------- >| |< -------- >| |< -------- >|
 *     第一个像素      第二个像素      第三个像素       第四个像素     第五个像素     第六个像素
 *   |< -------------------------------------- >| |< -------------------------------------- >|
 *                    第一行像素                                   第二行像素
 *
 *   理解了图片的存储之后，再开始编写代码。
 */


// 练习4，将彩色图片(rgb)转化为灰度图片
void rgb2gray(float *in, float *out, int h, int w) {
    /**
     * 编写这个函数，将一张彩色图片转化为灰度图片。以下是各个参数的含义：
     * (1) float *in:  指向彩色图片对应的内存区域（或者说数组）首地址的指针。
     * (2) float *out: 指向灰度图片对应的内存区域（或者说数组）首地址的指针。
     * (3) int h:      height，即图片的高度。
     * (4) int w:      width，即图片的宽度。
     *
     * 提示：
     * (1) in数组只管读取就行了，别修改它的值。out数组只修改不读取。
     * (2) 利用公式 V = 0.1140 * B  + 0.5870 * G + 0.2989 * R 计算彩色图片每个
     *     像素对应的灰度值，写到灰度图片相同的位置中就行。
     * (3) 使用for循环来遍历每个位置。利用图片在内存中的存储顺序，计算出每个位置像素
     *     的地址。
     *
     * 考点：
     * (1) for循环的使用。
     * (2) 内存的访问。
     */

    // IMPLEMENT YOUR CODE HERE
    for (int i = 0; i < h; i++) {
       
        for (int j = 0; j < w; j++) {
           
            int index = i * w * 3 + j * 3;
           
            float R = in[index];
            float G = in[index + 1];
            float B = in[index + 2];
            
            float V = 0.1140 * B + 0.5870 * G + 0.2989 * R;
            out[i * w + j] = V;
        }
    }
}
    // ...


// 练习5，实现图像处理算法 resize：缩小或放大图像
void resize(float *in, float *out, int h, int w, int c, float scale) {
    /**
     * 图像处理知识：
     *  1.单线性插值法
     *      假设有两个已知 点1(x1, y1) 和 点2(x2, y2)，
     *      点1 的值为v1，点2 的值为v2，
     *      待插值点 (x, y)处于 点1 和 点2 中间，值为 v，
     *      如下图所示(*表示点，/表示三个点在一条直线上)：
     *
     *                                * (x2, y2), v2
     *                               /
     *                              /
     *                             * (x, y), v
     *                            /
     *                           * (x1, y1), v1
     *
     *      则满足下面的条件：
     *                    x2 - x          x - x1
     *          v = v1 * ———————— + v2 * ————————
     *                    x2 - x1         x2 - x1
     *      也就是说，v的值是 点1 和 点2 的值的加权平均值，权重与到两点的距离相关
     *      (公式中的 x也可以是 y，因为是在一条直线上)。
     *
     *  2.双线性插值法
     *     2.1 由于图片是二维的，每个像素点有两个方向可以用来插值，所以可以使用双线性插值法。
     *     假设有四个已知 P1(x1, y2), P2(x2, y2), P3(x1, y1), P4(x2, y1)，
     *      如下图（看起来是在一条直线上就是在一条直线上）
     *
     *          P1(x1, y2)                      P2(x2, y2)
     *              *                               *
     *
     *                              * P(x, y)
     *
     *              *                               *
     *          P3(x1, y1)                      P4(x2, y1)
     *
     *      2.2 核心思想：
     *          双线性差值相当于三次差值，如下图所示：
     *
     *              P1(x1, y2)      Q1(x, y2)       P2(x2, y2)
     *                  *               *               *
     *
     *                                  * P(x, y)
     *
     *                  *               *               *
     *              P3(x1, y1)      Q2(x, y1)       P4(x2, y1)
     *
     *          先用单线性插值法计算出 Q1 和 Q2 的值，再用单线性插值法计算出 P 的值，即
     *                     x2 - x          x - x1
     *          Q1 = P1 * ———————— + P2 * ————————
     *                     x2 - x1         x2 - x1
     *
     *                     x2 - x          x - x1
     *          Q2 = P3 * ———————— + P4 * ————————
     *                     x2 - x1         x2 - x1
     *
     *                    y2 - y          y - y1
     *          Q = Q1 * ———————— + Q2 * ————————
     *                    y2 - y1         y2 - y1
     *
     *      2.3 化简：
     *          记 Dx = x2 - x1, Dy = y2 - y1, dx = x - x1, dy = y - y1，
     *
     *                     (Dx - dx)(Dy - dy)         dx(Dy - dy)
     *          Q = P1 * ———————————————————— + P2 * ————————————— +
     *                          Dx * Dy                 Dx * Dy
     *
     *                    (Dx - dx)dy           dxdy
     *              P3 * ————————————— + P4 * —————————
     *                      Dx * Dy            Dx * Dy
     *
     *  3. 双线性插值用于 resize 图片
     *      记 原图为 src，目标图为 dst，
     *         比例 dst宽高 = src宽高 * scale，
     *      设一个点 resize 后的坐标为 (x, y)，resize 前的坐标为 (x', y')，
     *      则有 x' = x / scale, y' = y / scale，
     *
     *      现在，对于每个目标图片中的像素点 (x, y)：
     *          1. 找到对应的源图片中的像素点 (x', y')
     *          2. 找到其在原图中的四个邻居点 (这四个邻居是相邻的四个点，组成一个正方形)
     *          3. 用双线性插值法计算出 该像素点 的值
     *
     *      不难发现，在这种情况下：Dx = Dy = 1（原图中相邻的四个像素横竖距离是1）
     *      所以，上面的公式可以化简为：
     *          Q = P1 * (1 - dx)(1 - dy) + P2 * dx(1 - dy)
     *            + P3 * (1 - dx)dy + P4 * dxdy
     * HINT:
     *     1. 对于每个 dst 中的像素点 (x, y)，先计算出其在 src 中的坐标 float(x0, y0)，
     *     2. 然后计算出其在 src 中的四个邻居点:
     *        x1 = static_cast<int>(x0), y1 = static_cast<int>(y0)
     *        上面这样可以直接将 float 通过下取整的方式转换为 int，
     *        剩下三个邻居就好找了
     *     3. 注意上面的方法中，四个邻居点的坐标可能会超出 src 的范围，
     *        所以需要对其进行边界检查
     */

    int new_h = h * scale, new_w = w * scale;
    // IMPLEMENT YOUR CODE HERE
  for (int dst_y = 0; dst_y < new_h; dst_y++) {
        for (int dst_x = 0; dst_x < new_w; dst_x++) {
            // 遍历每个颜色通道
            for (int channel = 0; channel < c; channel++) {
                // 1. 计算目标像素在原图像中的对应坐标（浮点数）
                float src_x = dst_x / scale;  // 原图像x坐标
                float src_y = dst_y / scale;  // 原图像y坐标
                
               
                int x1 = static_cast<int>(src_x);  // 左上角x坐标（下取整）
                int y1 = static_cast<int>(src_y);  // 左上角y坐标（下取整）
                int x2 = x1 + 1;  // 右上角x坐标
                int y2 = y1 + 1;  // 右下角y坐标
                
                
                x1 = (x1 < 0) ? 0 : (x1 >= w) ? w - 1 : x1;
                x2 = (x2 < 0) ? 0 : (x2 >= w) ? w - 1 : x2;
                y1 = (y1 < 0) ? 0 : (y1 >= h) ? h - 1 : y1;
                y2 = (y2 < 0) ? 0 : (y2 >= h) ? h - 1 : y2;
                
               
                float dx = src_x - x1;
                float dy = src_y - y1;
                
                
                int idx1 = (y1 * w + x1) * c + channel;  // P1(x1,y1)
                int idx2 = (y1 * w + x2) * c + channel;  // P2(x2,y1)
                int idx3 = (y2 * w + x1) * c + channel;  // P3(x1,y2)
                int idx4 = (y2 * w + x2) * c + channel;  // P4(x2,y2)
                
                float p1 = in[idx1];  // P1像素值
                float p2 = in[idx2];  // P2像素值
                float p3 = in[idx3];  // P3像素值
                float p4 = in[idx4];  // P4像素值
                
                float q1 = p1 * (1 - dx) + p2 * dx;  // 上边缘插值
                float q2 = p3 * (1 - dx) + p4 * dx;  // 下边缘插值
                float dst_val = q1 * (1 - dy) + q2 * dy;  // 最终插值结果
                
                int dst_idx = (dst_y * new_w + dst_x) * c + channel;
                out[dst_idx] = dst_val;
            }
        }
    }

}


// 练习6，实现图像处理算法：直方图均衡化
void hist_eq(float *in, int h, int w) {
    /**
     * 将输入图片进行直方图均衡化处理。参数含义：
     * (1) float *in: 输入的灰度图片。
     * (2) int h:     height，即图片的高度。
     * (3) int w:      width，即图片的宽度。
     *
     * 参考资料：
     * https://blog.csdn.net/qq_15971883/article/details/88699218
     * 其它的博客也行。
     *
     * 提示：
     * (1) 输入图片是灰度图，每个像素值是[0, 255]内的小数
     * (2) 灰度级个数为256，也就是{0, 1, 2, 3, ..., 255}
     * (3) 使用数组来实现灰度级 => 灰度级的映射
     */

    // IMPLEMENT YOUR CODE HERE
        int gray_level = 256;
    // 用于存储每个灰度级的像素数量
    int hist[gray_level] = {0};
    // 用于存储累积分布函数（CDF）
    float cdf[gray_level] = {0};
    // 用于存储灰度映射表
    float mapping[gray_level] = {0};

    // 步骤 1：统计灰度直方图
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            // 获取当前像素的灰度值
            int gray = static_cast<int>(in[i * w + j] + 0.5);
            // 确保灰度值在 0 - 255 范围内
            gray = (gray < 0) ? 0 : (gray > 255) ? 255 : gray;
            // 对应灰度级的像素数量加 1
            hist[gray]++;
        }
    }

    // 步骤 2：计算累积分布函数（CDF）
    cdf[0] = static_cast<float>(hist[0]) / (h * w);
    for (int i = 1; i < gray_level; i++) {
        cdf[i] = cdf[i - 1] + static_cast<float>(hist[i]) / (h * w);
    }

    // 步骤 3：构建灰度映射表
    for (int i = 0; i < gray_level; i++) {
        // 映射公式：新灰度值 = CDF[i] * 255
        mapping[i] = cdf[i] * 255;
    }

    // 步骤 4：根据映射表调整图像灰度
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            int gray = static_cast<int>(in[i * w + j] + 0.5);
            gray = (gray < 0) ? 0 : (gray > 255) ? 255 : gray;
            // 使用映射表得到新的灰度值
            in[i * w + j] = mapping[gray];
        }
    }
}

