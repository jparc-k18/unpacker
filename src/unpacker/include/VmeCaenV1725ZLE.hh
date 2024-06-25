// -*- C++ -*-

// Author: Koji Miwa

// this unpacker is used for DMA(BLT) data format

#ifndef HDDAQ__VME_V1725ZLE_UNPACKER_H
#define HDDAQ__VME_V1725ZLE_UNPACKER_H

#include "VmeModule.hh"

namespace hddaq
{
  namespace unpacker
  {
    
    class VmeCaenV1725ZLE
      : public VmeModule,
	private Uncopyable<VmeCaenV1725ZLE>
    {

    public:

      static const uint32_t k_local_tag_origin = 0U;
      static const uint32_t k_local_tag_max    = 0xffffffU;

      static const unsigned int k_header_mask  = 0x0f;
      static const unsigned int k_header_shift = 28U;
      static const unsigned int k_HEADER_MAGIC  = 0x0aU;//1010

      static const unsigned int k_event_size_mask = 0x0fffffff;
      static const unsigned int k_ch_mask_mask = 0xff;
      static const unsigned int k_ch_mask_shift1 = 0U;
      static const unsigned int k_ch_mask_shift2 = 24U;            

      static const unsigned int k_event_number_mask  = 0xffffff;

      static const unpacker_type k_type;
      static const unsigned int k_n_ch = 16U;
      static const unsigned int k_n_data_type = 1U;

      static const unsigned int k_baseline_mask = 0x3fff;      
      static const unsigned int k_baseline_shift = 16U;
      
      static const unsigned int k_ch_size_mask = 0xffff;

      static const unsigned int k_skip_header_mask  = 0x0f;
      static const unsigned int k_skip_header_shift = 28U;
      static const unsigned int k_SKIP_HEADER_MAGIC  = 0x08U;//1000

      static const unsigned int k_skip_sample_mask  = 0x0fffffff;

      static const unsigned int k_data_header_mask  = 0x03;
      static const unsigned int k_data_header_shift = 30U;
      static const unsigned int k_DATA_HEADER_MAGIC  = 0x0U;//00
      
      static const unsigned int k_data_mask  = 0x3fffU;
      static const unsigned int k_data_shift_even = 0U;
      static const unsigned int k_data_shift_odd  = 16U;


    public:
      VmeCaenV1725ZLE(const unpacker_type& type);
      virtual ~VmeCaenV1725ZLE();
      
    protected:
      //      virtual void check_data_format();
      virtual void decode();
      virtual void update_tag();
      virtual void resize_fe_data();

    };
    
  }
}
#endif
