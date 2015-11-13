#include <stm8s.h>
#include <stm8s_flash.h>

#include "platform_config.h"
#include "eemem.h"


/**
 * ��������� �������� ��������� 1 �������
 */
uint8_t eemem_get_temp1_delta() {
    return HWREG8(EEMEM_BASE_ADDR + OFFSETOF(eemem_map_t, temp1_delta));
}

/**
 * �������� �������� ��������� 1 �������
 */
void eemem_set_temp1_delta(uint8_t delta) {
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    
    HWREG8(EEMEM_BASE_ADDR + OFFSETOF(eemem_map_t, temp1_delta)) = delta;
    
    FLASH_Lock(FLASH_MEMTYPE_DATA);
}

/**
 * ��������� �������� ��������� 1 �������
 */
uint8_t eemem_get_temp2_delta() {
    return HWREG8(EEMEM_BASE_ADDR + OFFSETOF(eemem_map_t, temp2_delta));
}

/**
 * �������� �������� ��������� 1 �������
 */
void eemem_set_temp2_delta(uint8_t delta) {
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    
    HWREG8(EEMEM_BASE_ADDR + OFFSETOF(eemem_map_t, temp2_delta)) = delta;
    
    FLASH_Lock(FLASH_MEMTYPE_DATA);
}

/**
 * ��������� ��������� �����������
 */
uint8_t eemem_get_state() {
    return HWREG8(EEMEM_BASE_ADDR + OFFSETOF(eemem_map_t, state));
}

/**
 * �������� ��������� �����������
 */
void eemem_set_state(uint8_t state) {
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    
    HWREG8(EEMEM_BASE_ADDR + OFFSETOF(eemem_map_t, state)) = state;
    
    FLASH_Lock(FLASH_MEMTYPE_DATA);
}

/**
 * ��������� ��������� �����������
 */
uint8_t eemem_get_intensity() {
    return HWREG8(EEMEM_BASE_ADDR + OFFSETOF(eemem_map_t, intensity));
}

/**
 * �������� ��������� �����������
 */
void eemem_set_intensity(uint8_t intensity) {
    FLASH_Unlock(FLASH_MEMTYPE_DATA);
    
    if(intensity == 0xFF)
        intensity = 0;
    
    if(intensity == 9)
        intensity = 8;
    
    HWREG8(EEMEM_BASE_ADDR + OFFSETOF(eemem_map_t, intensity)) = intensity;
    
    FLASH_Lock(FLASH_MEMTYPE_DATA);
}
