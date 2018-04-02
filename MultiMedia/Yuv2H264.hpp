#pragma once
#include <string>
extern "C" {
#include "x264/x264.h"
};
#pragma comment (lib, "libx264-152.lib")

void X264EncodeFile(const std::string& str_file_name, int n_frame_width, int n_frame_height)
{
	FILE* src_file_ptr = fopen(str_file_name.c_str(), "rb");
	FILE* dst_file_ptr = fopen("Output.h264", "wb");

	if (!src_file_ptr) {
		printf ("Can not open source file\n");
		return;
	}
	if (!dst_file_ptr) {
		printf("Can not create or open destination file\n");
		return;
	}

	int i_nal_count = 0;
	x264_nal_t* nal_ptr = nullptr;
	x264_t* handle_ptr = nullptr;
	x264_picture_t* pic_in_ptr = (x264_picture_t*)malloc(sizeof(x264_picture_t));
	x264_picture_t* pic_out_ptr = (x264_picture_t*)malloc(sizeof(x264_picture_t));
	x264_param_t* param_ptr = (x264_param_t*)malloc(sizeof(x264_param_t));

	x264_param_default(param_ptr);
	param_ptr->i_width = n_frame_width;
	param_ptr->i_height = n_frame_height;
	param_ptr->i_csp = X264_CSP_I420;
	x264_param_apply_profile(param_ptr, x264_profile_names[0]);

	handle_ptr = x264_encoder_open(param_ptr);
	x264_picture_init(pic_out_ptr);
	x264_picture_alloc(pic_in_ptr, param_ptr->i_csp, param_ptr->i_width, param_ptr->i_height);

	int i_y_size = param_ptr->i_width * param_ptr->i_height;
	while (1 == fread(pic_in_ptr->img.plane[0], i_y_size, 1, src_file_ptr)
		&& 1 == fread(pic_in_ptr->img.plane[1], i_y_size / 4, 1, src_file_ptr)
		&& 1 == fread(pic_in_ptr->img.plane[2], i_y_size / 4, 1, src_file_ptr))
	{
		if (x264_encoder_encode(handle_ptr, &nal_ptr, &i_nal_count, pic_in_ptr, pic_out_ptr) < 0) {
			printf("Encode Error\n");
		}
		for (int i = 0; i < i_nal_count; ++i)
		{
			fwrite(nal_ptr[i].p_payload, 1, nal_ptr[i].i_payload, dst_file_ptr);
		}
	}

	x264_picture_clean(pic_in_ptr);
	x264_encoder_close(handle_ptr);
	handle_ptr = nullptr;

	free(pic_in_ptr);
	pic_in_ptr = nullptr;
	free(pic_out_ptr);
	pic_out_ptr = nullptr;
	free(param_ptr);
	param_ptr = nullptr;

	fclose(src_file_ptr);
	fclose(dst_file_ptr);
}

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavutil/opt.h"
#include "libavformat/avformat.h"
}
#pragma comment (lib, "avcodec.lib")
#pragma comment (lib, "avformat.lib")
#pragma comment (lib, "avutil.lib")

void FFmpegEncodeFile(const std::string& str_file_name, int n_frame_width, int n_frame_height)
{
	FILE* src_file_ptr = fopen(str_file_name.c_str(), "rb");
	av_register_all();
	AVFormatContext* format_context_ptr = avformat_alloc_context();
	AVOutputFormat* output_ptr = av_guess_format(nullptr, "Output.h264", nullptr);
	format_context_ptr->oformat = output_ptr;

	if (avio_open(&format_context_ptr->pb, "Output.h264", AVIO_FLAG_READ_WRITE) < 0) {
		printf("Can not create or open destination file\n");
		return;
	}

	AVStream* stream_ptr = avformat_new_stream(format_context_ptr, 0);
	if (!stream_ptr)
		return;

	AVCodecContext* codec_context_ptr = stream_ptr->codec;
	codec_context_ptr->codec_id = output_ptr->video_codec;
	codec_context_ptr->codec_type = AVMEDIA_TYPE_VIDEO;
	codec_context_ptr->pix_fmt = AV_PIX_FMT_YUV420P;
	codec_context_ptr->width = n_frame_width;
	codec_context_ptr->height = n_frame_height;
	codec_context_ptr->bit_rate = 400000;
	codec_context_ptr->gop_size = 250;
	codec_context_ptr->time_base.den = 25;
	codec_context_ptr->time_base.num = 1;
	codec_context_ptr->qmin = 15;
	codec_context_ptr->qmax = 51;
	codec_context_ptr->max_b_frames = 3;

	AVDictionary* dic_ptr = nullptr;
	if (AV_CODEC_ID_H264 == codec_context_ptr->codec_id) {
		
		av_dict_set(&dic_ptr, "preset", "ultrafast", 0);
		av_dict_set(&dic_ptr, "tune", "zero-latency", 0);
	}

	av_dump_format(format_context_ptr, 0, "Output.h264", 1);

	AVCodec* codec_ptr = avcodec_find_encoder(codec_context_ptr->codec_id);
	if (!codec_ptr)
		return;
	if (avcodec_open2(codec_context_ptr, codec_ptr, &dic_ptr) < 0) {
		return;
	}

	AVFrame* frame_ptr = av_frame_alloc();
	int i_pic_size = avpicture_get_size(codec_context_ptr->pix_fmt, codec_context_ptr->width, codec_context_ptr->height);
	unsigned char* buffer_ptr = (unsigned char*)av_malloc(i_pic_size);
	avpicture_fill((AVPicture*)frame_ptr, buffer_ptr, codec_context_ptr->pix_fmt, codec_context_ptr->width, codec_context_ptr->height);

	avformat_write_header(format_context_ptr, nullptr);
	AVPacket packet;
	av_new_packet(&packet, i_pic_size);

	int i_y_size = codec_context_ptr->width * codec_context_ptr->height;
	int i = 0;
	while (1 == fread(buffer_ptr, i_y_size*3/2, 1, src_file_ptr))
	{
		frame_ptr->data[0] = buffer_ptr;
		frame_ptr->data[1] = buffer_ptr + i_y_size;
		frame_ptr->data[2] = buffer_ptr + i_y_size + i_y_size / 4;
		frame_ptr->pts = (i++)*(stream_ptr->time_base.den) / ((stream_ptr->time_base.num) * 25);
		int i_got_size = 0;
		if (avcodec_encode_video2(codec_context_ptr, &packet, frame_ptr, &i_got_size) < 0) {
			return;
		}
		if (1 == i_got_size) {
			packet.stream_index = stream_ptr->index;
			av_write_frame(format_context_ptr, &packet);
			av_free_packet(&packet);
		}
	}

	if (stream_ptr) {
		avcodec_close(stream_ptr->codec);
		av_free(frame_ptr);
		av_free(buffer_ptr);
	}
	avio_close(format_context_ptr->pb);
	avformat_free_context(format_context_ptr);

	fclose(src_file_ptr);
}