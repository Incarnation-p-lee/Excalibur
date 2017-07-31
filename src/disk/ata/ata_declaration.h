#ifndef SRC_DISK_ATA_DECLARATION_H
#define SRC_DISK_ATA_DECLARATION_H

static inline bool ata_device_info_io_port_legal_p(s_ata_dev_io_port_t *io_port);
static inline bool ata_device_info_legal_p(s_ata_dev_info_t *dev_info);
static inline bool ata_device_status_busy_p(uint8 status);
static inline bool ata_device_status_device_ready_p(uint8 status);
static inline bool ata_device_status_error_p(uint8 status);
static inline bool ata_device_status_readable_p(uint8 status);
static inline bool ata_device_status_seek_complete_p(uint8 status);
static inline s_ata_dev_info_t * ata_device_info(uint32 i);
static inline s_ata_dev_io_port_t * ata_device_info_io_port(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_cylinder_read(uint16 status_port, uint16 port_low, uint16 port_high);
static inline uint16 ata_device_drive_identify(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_cmd_port(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_control_port(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_cylinder_count(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_cylinder_high_port(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_cylinder_low_port(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_data_port(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_drive_id(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_drive_port(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_head_count(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_io_cmd_port(s_ata_dev_io_port_t *io_port);
static inline uint16 ata_device_info_io_control_port(s_ata_dev_io_port_t *io_port);
static inline uint16 ata_device_info_io_cylinder_high_port(s_ata_dev_io_port_t *io_port);
static inline uint16 ata_device_info_io_cylinder_low_port(s_ata_dev_io_port_t *io_port);
static inline uint16 ata_device_info_io_data_port(s_ata_dev_io_port_t *io_port);
static inline uint16 ata_device_info_io_drive_port(s_ata_dev_io_port_t *io_port);
static inline uint16 ata_device_info_io_lba_low_port(s_ata_dev_io_port_t *io_port);
static inline uint16 ata_device_info_io_sector_count_port(s_ata_dev_io_port_t *io_port);
static inline uint16 ata_device_info_io_status_port(s_ata_dev_io_port_t *io_port);
static inline uint16 ata_device_info_lba_high_port(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_lba_low_port(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_lba_mid_port(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_sector_bytes(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_sector_count_port(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_status_port(s_ata_dev_info_t *dev_info);
static inline uint16 ata_device_info_track_sector(s_ata_dev_info_t *dev_info);
static inline uint32 ata_device_info_limit(void);
static inline uint32 ata_device_info_type(s_ata_dev_info_t *dev_info);
static inline void ata_device_drive_info_indentify(s_ata_dev_info_t *dev);
static inline void ata_device_drive_set(uint16 port, uint8 val);
static inline void ata_device_info_cylinder_count_set(s_ata_dev_info_t *dev_info, uint16 count);
static inline void ata_device_info_head_count_set(s_ata_dev_info_t *dev_info, uint16 count);
static inline void ata_device_info_print(void);
static inline void ata_device_info_sector_bytes_set(s_ata_dev_info_t *dev_info, uint16 val);
static inline void ata_device_info_track_sector_set(s_ata_dev_info_t *dev_info, uint16 val);
static inline void ata_device_info_type_print(uint32 type);
static inline void ata_device_info_type_set(s_ata_dev_info_t *dev_info, uint32 type);
static inline void ata_device_loop_util_data_ready(uint16 status_port);
static inline void ata_device_sector_read_i(s_disk_buf_t *disk_buf, uint32 device_id, uint32 lba);
static inline void ata_device_software_reset(uint16 port);
static inline void ata_device_type_detect(void);
static inline void ata_device_type_detect_i(s_ata_dev_info_t *dev_info);
void ata_device_detect(void);
void ata_device_sector_read(s_disk_buf_t *disk_buf, uint32 device_id, uint32 lba);

#endif
