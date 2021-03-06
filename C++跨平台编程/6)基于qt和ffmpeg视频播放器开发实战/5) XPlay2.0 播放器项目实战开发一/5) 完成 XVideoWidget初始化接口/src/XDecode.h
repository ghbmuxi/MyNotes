#pragma once
struct AVCodecParameters;
struct AVCodecContext;
struct AVPacket;
struct AVFrame;
#include <mutex>

class XDecode
{
public:

	// 打开解码器,不管成功与否都释放codecpar空间
	virtual bool Open(AVCodecParameters *codecpar);

	// 发送到解码线程, 不管成功与否都释放pkt空间(对象和媒体内容)
	virtual bool Send(AVPacket *pkt);

	// 获取解码数据, 一次send可能需要多次Recv
	// 每次复制一份, 由调用者释放 av_frame_free()
	virtual AVFrame* Recv();

	virtual void Close();
	virtual void Clear();

	XDecode();
	virtual ~XDecode();

public:
	bool _isAudio = false;

protected:
	AVCodecContext *_codec = 0;
	std::mutex _mux;
};

