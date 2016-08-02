// -*- C++ -*-

// Author: Tomonori Takahashi

#include "VmeCaenV1724.hh"

#include <algorithm>

#include "std_ostream.hh"
#include "HexDump.hh"
#include "defines.hh"

namespace hddaq
{
namespace unpacker
{

  const defines::unpacker_type VmeCaenV1724::k_type = "VmeCaenV1724";

//______________________________________________________________________________
VmeCaenV1724::VmeCaenV1724(const unpacker_type& type)
  : VmeModule(type)
{
}

//______________________________________________________________________________
VmeCaenV1724::~VmeCaenV1724()
{
}

//______________________________________________________________________________
// void
// VmeCaenV1724::check_data_format()
// {
//   uint32_t header = *m_module_data_first; 


//   if (((header >> k_data_type_shift) & k_data_type_mask) != k_HEADER_MAGIC)
//     m_error_state.set(defines::k_header_bit);
  
//   return;
// }

//______________________________________________________________________________
void
VmeCaenV1724::decode()
{
  iterator_list::const_iterator f_begin = m_first_list.begin();
  iterator_list::const_iterator f_end   = m_first_list.end();
  for (iterator_list::const_iterator f  = f_begin;  f!=f_end; ++f)
    {
      iterator first = *f;
      m_vme_header = reinterpret_cast<VmeModule::Header*>(&*first);
      m_module_data_first = first + VmeModule::k_header_size;

      const uint32_t* buf = reinterpret_cast<uint32_t*>(&*m_module_data_first);
      
      unsigned int data_size = m_vme_header->m_data_size-VmeModule::k_header_size;;
      
      // decode from here
      
      uint32_t header_id  = ((buf[0] >> k_headerid_shift) & k_headerid_mask);
      if(header_id != 0x0A){
	//where is header!?
      }
      uint32_t event_size = ((buf[0] >> k_evsize_shift)   & k_evsize_mask);
      uint32_t data_format= ((buf[1] >> k_format_shift)   & k_format_mask);
      uint32_t ch_mask    = ((buf[1] >> k_chmask_shift)   & k_chmask_mask);
      
      unsigned int ch_num = 0;
      for(int i=0;i<k_n_ch;i++){
	ch_num += ((ch_mask>>i) & 0x01);
      }
      
      //default mode
      if(data_format == 0){
	uint32_t sample_size = (event_size-4)/ch_num;
	uint32_t i=4;
	for(uint32_t ch = 0 ; ch<k_n_ch; ch++ ){
	  uint32_t ch_sample = ((ch_mask >> ch) & 0x01 ) *sample_size;
	  for(int j=0; j<ch_sample; j++, i++){
	    uint32_t data_even = ((buf[i] >> k_data_shift_even) & k_data_mask);
	    fill(ch, 0, data_even);
	    uint32_t data_odd = ((buf[i] >> k_data_shift_odd) & k_data_mask);
	    fill(ch, 0, data_odd);
	  }
	}
      }
      
      /*
      for (int i=0; i<data_size; i++) {
	uint32_t ch          = ((buf[i] >> k_ch_shift) & k_ch_mask);
	uint32_t sample_size = ((buf[i] >> k_sample_shift) & k_sample_mask);
	for (int j=0; j<sample_size; j++, i++) {
	  uint32_t data_even = ((buf[i] >> k_data_shift_even) & k_data_mask);
	  fill(ch, 0, data_even);
	  uint32_t data_odd = ((buf[i] >> k_data_shift_odd) & k_data_mask);
	  fill(ch, 0, data_odd);
// 	  std::cerr << "VmeCaenV1724::decode unknown data type : " << std::hex << data_type 
// 		    << "(" << (buf[i]) << ")" << "\n" << std::dec;
	  
	}
      }
      */
      
    }
  return;
}

//______________________________________________________________________________
void
VmeCaenV1724::resize_fe_data()
{
  m_fe_data.resize(k_n_ch);
  for(unsigned int i = 0; i<k_n_ch; ++i){
    m_fe_data[i].resize(k_n_data_type);
  }

  return;
}
}
}

