// -*- C++ -*-

// Author: Shuhei Hayakawa

#include "VmeCaenV792.hh"

#include <algorithm>

#include "std_ostream.hh"
#include "HexDump.hh"
#include "defines.hh"

namespace hddaq
{
namespace unpacker
{

  const defines::unpacker_type VmeCaenV792::k_type = "VmeCaenV792";

//______________________________________________________________________________
VmeCaenV792::VmeCaenV792(const unpacker_type& type)
  : VmeModule(type)
{
}

//______________________________________________________________________________
VmeCaenV792::~VmeCaenV792()
{
}

//______________________________________________________________________________
void
VmeCaenV792::check_data_format()
{
  uint32_t header = *m_module_data_first; 
  if (((header>>k_word_type_shift)&k_word_type_mask) != k_HEADER_MAGIC)
    m_error_state.set(defines::k_header_bit);
  return;
}

//______________________________________________________________________________
void
VmeCaenV792::decode()
{
  iterator_list::const_iterator f_begin = m_first_list.begin();
  iterator_list::const_iterator f_end   = m_first_list.end();
  for (iterator_list::const_iterator f=f_begin; f!=f_end; ++f) {
    iterator first = *f;
    m_vme_header = reinterpret_cast<VmeModule::Header*>(&*first);
    m_module_data_first = first + VmeModule::k_header_size;
    
    const uint32_t* buf = reinterpret_cast<uint32_t*>(&*m_module_data_first);
    unsigned int data_size = m_vme_header->m_data_size - VmeModule::k_header_size;
    
    for (unsigned int i=0; i<data_size; i++) {
      uint32_t word_type = ((buf[i]>>k_word_type_shift)&k_word_type_mask);
      switch(word_type){
      case k_HEADER_MAGIC:
	break;
      case k_DATA_MAGIC:
	{
	  uint32_t ch   = ((buf[i]>>k_channel_shift) & k_channel_mask);
	  uint32_t data = ((buf[i]>>k_data_shift)    & k_data_mask);
	  //uint32_t overflow = ((buf[i]>>k_overflow_shift) & k_overflow_mask);
	  //std::cout<<"#D VmeCaenV792::decode()   ch: "<<ch<<"\tdata: "<<data<<std::endl;
	  fill(ch, k_adc, data);
	}
	break;
      case k_FOOTER_MAGIC:
	break;
      case k_INVALID_MAGIC:
	// std::cerr<<"#W VmeCaenV792::decode() not valid datum: "
	// 	 <<std::hex<<word_type<<" ("<<buf[i]<<")"<<std::endl<<std::dec;
	break;
      default:
	std::cerr<<"#E VmeCaenV792::decode() unknown word type: "
		 <<std::hex<<word_type<<" ("<<buf[i]<<")"<<std::endl<<std::dec;
      }//switch(word_type)
    }//for(i)
  }//for(f)
  return;
}
  
//______________________________________________________________________________
void
VmeCaenV792::resize_fe_data()
{
  m_fe_data.resize(k_n_channel);
  for(unsigned int i = 0; i<k_n_channel; ++i){
    m_fe_data[i].resize(k_n_data_type);
  }

  return;
}

}
}
