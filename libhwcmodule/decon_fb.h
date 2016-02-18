
#ifndef __DECON_FB_H__
#define __DECON_FB_H__

/* S3C_FB_MAX_WIN
 * Set to the maximum number of windows that any of the supported hardware
 * can use. Since the platform data uses this for an array size, having it
 * set to the maximum of any version of the hardware can do is safe.
 */
#define S3C_FB_MAX_WIN	(5)
#define S3C_WIN_UPDATE_IDX      (5)

struct s3c_fb_user_window {
	int x;
	int y;
};

struct s3c_fb_user_plane_alpha {
	int		channel;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
};

struct s3c_fb_user_chroma {
	int		enabled;
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
};

struct s3c_fb_user_ion_client {
	int	fd;
	int	offset;
};

enum s3c_fb_pixel_format {
	S3C_FB_PIXEL_FORMAT_RGBA_8888 = 0,
	S3C_FB_PIXEL_FORMAT_RGBX_8888 = 1,
	S3C_FB_PIXEL_FORMAT_RGBA_5551 = 2,
	S3C_FB_PIXEL_FORMAT_RGB_565 = 3,
	S3C_FB_PIXEL_FORMAT_BGRA_8888 = 4,
	S3C_FB_PIXEL_FORMAT_BGRX_8888 = 5,
	S3C_FB_PIXEL_FORMAT_MAX = 6,
};

enum s3c_fb_blending {
	S3C_FB_BLENDING_NONE = 0,
	S3C_FB_BLENDING_PREMULT = 1,
	S3C_FB_BLENDING_COVERAGE = 2,
	S3C_FB_BLENDING_MAX = 3,
};

enum otf_status {
	S3C_FB_DMA,
	S3C_FB_LOCAL,
	S3C_FB_READY_TO_LOCAL,
	S3C_FB_S_STREAM,
};

struct s3c_fb_win_config {
	enum {
		S3C_FB_WIN_STATE_DISABLED = 0,
		S3C_FB_WIN_STATE_COLOR,
		S3C_FB_WIN_STATE_BUFFER,
		S3C_FB_WIN_STATE_OTF,
		S3C_FB_WIN_STATE_UPDATE,
	} state;

	union {
		__u32 color;
		struct {
			int				fd;
			__u32				offset;
			__u32				stride;
			enum s3c_fb_pixel_format	format;
			enum s3c_fb_blending		blending;
			int				fence_fd;
			int				plane_alpha;
		};
	};

	int	x;
	int	y;
	__u32	w;
	__u32	h;
	int orientation;
};

struct s3c_fb_win_config_data {
	int	fence;
#ifdef CONFIG_FB_WINDOW_UPDATE
	struct s3c_fb_win_config config[S3C_FB_MAX_WIN + 1];
#else
	struct s3c_fb_win_config config[S3C_FB_MAX_WIN];
#endif
};

/* IOCTL commands */
#define S3CFB_WIN_POSITION		_IOW('F', 203, \
						struct s3c_fb_user_window)
#define S3CFB_WIN_SET_PLANE_ALPHA	_IOW('F', 204, \
						struct s3c_fb_user_plane_alpha)
#define S3CFB_WIN_SET_CHROMA		_IOW('F', 205, \
						struct s3c_fb_user_chroma)
#define S3CFB_SET_VSYNC_INT		_IOW('F', 206, __u32)

#define S3CFB_GET_ION_USER_HANDLE	_IOWR('F', 208, \
						struct s3c_fb_user_ion_client)
#define S3CFB_WIN_CONFIG		_IOW('F', 209, \
						struct s3c_fb_win_config_data)
#define S3CFB_WIN_PSR_EXIT 		_IOW('F', 210, int)
#endif
