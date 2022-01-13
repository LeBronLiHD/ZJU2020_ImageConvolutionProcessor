# ImageConvolutionProcess_Qt

- 面向对象编程(C++)课程大作业
- 左右视窗分别显示原图片与处理后图片
- 左下角部分为独立的计时器
  - 开始计时```StartTimer```
  - 结束计时```EngTimer```
  - 计时器2000ms测试```2000ms Test```
- 中间部分
  - ```Exit```：退出应用
  - ```Help```：创作人员信息
  - ```Read Image```：读取图片
  - ```Clear Image```：清除图片
  - ```Random 3*3 Matrix```：随机生成卷积核
  - ```Customize 3*3 Matrix```：自定义卷积核
  - ```Clear 3*3 Matrix```：清除卷积核
  - 底部```Convolution Core```：显示当前卷积核
- 右下角部分为图像处理部分
  - ```Image Pixel```：显示图像像素信息
  - ```Gray```：图像灰度处理
  - ```Binary```：图像二值化处理
  - ```Light```：亮度提升处理
  - ```Convolution```：图像卷积运算，同时记录卷积运算用时
- 注意事项
  - 笔者采用绝对路径```F:\\Timer_One_Qt```使用软件，不同设备上运行可能导致背景加载、读图与图片处理错误，再也不用绝对路径了，还是相对路径方便
  - 软件版本为```Qt Creator 5.9.0```，不同版本可能导致因为软件配置路径不同导致项目运行失败
- 运行截图
  - 灰度变化
 
![1](https://github.com/LeBronLiHD/ZJU2020_ImageConvolutionProcessor/blob/main/imgRes/gray.png)

  - 二值化处理

![2](https://github.com/LeBronLiHD/ZJU2020_ImageConvolutionProcessor/blob/main/imgRes/binary.png)

  - 像素计算

![3](https://github.com/LeBronLiHD/ZJU2020_ImageConvolutionProcessor/blob/main/imgRes/imagePixel.png)

  - 亮度变化

![4](https://github.com/LeBronLiHD/ZJU2020_ImageConvolutionProcessor/blob/main/imgRes/light.png)

  - 卷积计算与计时

![5](https://github.com/LeBronLiHD/ZJU2020_ImageConvolutionProcessor/blob/main/imgRes/UI.png)


