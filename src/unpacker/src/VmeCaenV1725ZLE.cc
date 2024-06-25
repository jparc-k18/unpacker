// -*- C++ -*-

// Author: Koji Miwa

#include "VmeCaenV1725ZLE.hh"

#include <algorithm>

#include "std_ostream.hh"
#include "HexDump.hh"
#include "defines.hh"

namespace hddaq
{
namespace unpacker
{

  const defines::unpacker_type VmeCaenV1725ZLE::k_type = "VmeCaenV1725ZLE";

//______________________________________________________________________________
VmeCaenV1725ZLE::VmeCaenV1725ZLE(const unpacker_type& type)
  : VmeModule(type)
{
  Tag& orig = m_tag[k_tag_origin].back();
  orig.m_local = k_local_tag_origin;

  Tag& max = m_tag[k_tag_max].back();
  max.m_local = k_local_tag_max;
  max.m_event = 0;
  max.m_spill = 0;
}

//______________________________________________________________________________
VmeCaenV1725ZLE::~VmeCaenV1725ZLE()
{
}

//______________________________________________________________________________
void
VmeCaenV1725ZLE::decode()
{
  iterator_list::const_iterator f_begin = m_first_list.begin();
  iterator_list::const_iterator f_end   = m_first_list.end();
  for (iterator_list::const_iterator f  = f_begin;  f!=f_end; ++f)
    {
      iterator first = *f;
      m_vme_header = reinterpret_cast<VmeModule::Header*>(&*first);
      m_module_data_first = first + VmeModule::k_header_size;

      const uint32_t* buf = reinterpret_cast<uint32_t*>(&*m_module_data_first);

      uint32_t header_type = ((buf[0] >> k_header_shift) & k_header_mask);
      if(header_type != k_HEADER_MAGIC){
	cerr << "\n#E " << header_type << " vme module header \n"  << std::endl;
	return;
      }

      uint32_t event_size  = (buf[0] & k_event_size_mask);
      //for (unsigned int i=0; i<event_size; i++) {
      //std::cout << std::dec << i << " : "  << std::hex << buf[i] << std::endl;
      //}
      
      uint32_t ch_mask1 = (buf[1] & k_ch_mask_mask);
      uint32_t ch_mask2 = ((buf[2] >> k_ch_mask_shift2) & k_ch_mask_mask);
      uint32_t ch_mask = (ch_mask2 << 8) + ch_mask1;
      
      unsigned int ch_num = 0;
      for(unsigned int i=0; i<k_n_ch; i++)
	ch_num += ((ch_mask>>i) & 0x01);

      if(1){//PedSup mode
	unsigned int ZLEdata[k_n_ch][20000];
	unsigned int line=4;
	unsigned int d_size[k_n_ch];

	for(unsigned int ch =0;ch<k_n_ch;ch++){
	  int tch = ch;// + 8*no;
	  if( (ch_mask>>ch &0x01 )==0x01){
	    d_size[tch] = (buf[line++] & k_ch_size_mask) - 1;
	    for(unsigned int j=0;j<d_size[tch];j++)
	      ZLEdata[tch][j] = buf[line++];
	  }
	  else
	    d_size[tch] =0;

	  for(unsigned int j=0;j<d_size[tch];j++){
	    if (((ZLEdata[tch][j]>>k_skip_header_shift)&k_skip_header_mask)
		== k_SKIP_HEADER_MAGIC) {
	      unsigned int nskip = ZLEdata[tch][j] & k_skip_sample_mask;
	      for(unsigned int k=0;k<nskip;k++){
		fill(tch, 0, 0xFFFF);
		fill(tch, 0, 0xFFFF);
	      }
	    } else if (((ZLEdata[tch][j]>>k_data_header_shift)&k_data_header_mask)
		== k_DATA_HEADER_MAGIC) {
	      unsigned int data_even =
		((ZLEdata[tch][j] >> k_data_shift_even) & k_data_mask);
	      fill(tch, 0, data_even);
	      unsigned int data_odd =
		((ZLEdata[tch][j] >> k_data_shift_odd) & k_data_mask);
	      fill(tch, 0, data_odd);
	    }
	  }
	}
      }

    }
  return;
}
//______________________________________________________________________________
void
VmeCaenV1725ZLE::update_tag()
{
  m_module_data_first = m_data_first + VmeModule::k_header_size;

  uint32_t buf = *(m_module_data_first+2);
  uint32_t event_number = buf & k_event_number_mask;
  //  std::cout << event_number << std::endl;

  Tag& tag = m_tag[k_tag_current].back();
  tag.m_local = event_number;
  m_has_tag.set(k_local);
}


//______________________________________________________________________________
void
VmeCaenV1725ZLE::resize_fe_data()
{
  m_fe_data.resize(k_n_ch);
  for(unsigned int i = 0; i<k_n_ch; ++i){
    m_fe_data[i].resize(k_n_data_type);
  }

  return;
}

}
}
