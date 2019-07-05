#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "py/mperrno.h"
#include "py/mphal.h"
#include "py/runtime.h"

#include <driver_ssd1306.h>

#ifdef CONFIG_DRIVER_SSD1306_ENABLE

static mp_obj_t ssd1306_write(mp_obj_t _data) {
	mp_uint_t len;
	if (!MP_OBJ_IS_TYPE(_data, &mp_type_bytes)) {
		mp_raise_ValueError("Expected a bytestring like object.");
		return mp_const_none;
	}
	uint8_t *data = (uint8_t *)mp_obj_str_get_data(_data, &len);
	if (len != SSD1306_BUFFER_SIZE) {
		mp_raise_ValueError("Wrong buffer size!");
		return mp_const_none;
	}
	driver_ssd1306_write(data);
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(ssd1306_write_obj, ssd1306_write);

/*static mp_obj_t ssd1306_flip(mp_obj_t _flip) {
	bool flip = mp_obj_get_int(_flip);
	driver_ssd1306_set_rotation(flip);
	return mp_const_none;
}
static MP_DEFINE_CONST_FUN_OBJ_1(ssd1306_flip_obj, ssd1306_flip);*/

static const mp_rom_map_elem_t ssd1306_module_globals_table[] = {
	{MP_ROM_QSTR(MP_QSTR_write), MP_ROM_PTR(&ssd1306_write_obj)},
	//{MP_ROM_QSTR(MP_QSTR_set_rotatation), MP_ROM_PTR(&ssd1306_flip_obj)},
};

static MP_DEFINE_CONST_DICT(ssd1306_module_globals, ssd1306_module_globals_table);

const mp_obj_module_t ssd1306_module = {
	.base = {&mp_type_module},
	.globals = (mp_obj_dict_t *)&ssd1306_module_globals,
};

#endif // CONFIG_DRIVER_I2C_ENABLE
