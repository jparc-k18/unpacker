// -*- C++ -*-

// Author: Tomonori Takahashi

// this unpacker is used for DMA(BLT) data format

#ifndef HDDAQ__VME_CAEN_V1724_UNPACKER_H
#define HDDAQ__VME_CAEN_V1724_UNPACKER_H

#include "VmeModule.hh"

namespace hddaq
{
  namespace unpacker
  {
    
    class VmeCaenV1724
      : public VmeModule,
	private Uncopyable<VmeCaenV1724>
    {

    public:
      static const unpacker_type k_type;
      static const unsigned int k_n_ch           = 8U;
      static const unsigned int k_n_data_type    = 1U;
      
      static const unsigned int k_headerid_mask  = 0x0fU;
      static const unsigned int k_headerid_shift = 28U;

      static const unsigned int k_evsize_mask    = 0x0fffffffU;
      static const unsigned int k_evsize_shift   = 0U;

      static const unsigned int k_format_mask    = 0x01U;
      static const unsigned int k_format_shift   = 24U;

      static const unsigned int k_chmask_mask    = 0xffU;
      static const unsigned int k_chmask_shift   = 0U;

      
      static const unsigned int k_ch_mask        = 0x7U;
      static const unsigned int k_ch_shift       = 24U;

      static const unsigned int k_sample_mask    = 0xffffffU;
      static const unsigned int k_sample_shift   = 0U;

      static const unsigned int k_data_mask      = 0x3fffU;
      static const unsigned int k_data_shift_even = 0U;
      static const unsigned int k_data_shift_odd  = 16U;

    public:
      VmeCaenV1724(const unpacker_type& type);
      virtual ~VmeCaenV1724();
      
    protected:
      //      virtual void check_data_format();
      virtual void decode();
      virtual void resize_fe_data();

    };
    
  }
}
#endif
