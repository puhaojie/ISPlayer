# ISPlayer


#1、FFDemux() 构造方法中初始化FFmpeg
#2、FFDemux对象的Open() 打开连接
#3、IDemux对象中的main()是对封装数据的读取,该方法是核心方法，但并不是被调用，而是XThread#ThreadMain()方法
#4、介于XThread和IDemux之间的IObserver是观察者，将读取解封装后的数据XData通知到相应的观察者，并进行对应的解码