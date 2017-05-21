#include "stdafx.h"
#include "net_buffer.h"

static const int MAX_BUFFER_BLOCK = 4096;

buffer_base::buffer_base(uint32_t blocklen, uint32_t maxlen):	
	m_buf(blocklen)
	,m_maxlen(maxlen)
	,m_release(0)
{
	if (maxlen<=blocklen)
	{
		m_maxlen = blocklen*2;
	}
}

buffer_base::~buffer_base()
{

}

bool buffer_base::check_len(uint32_t len)
{
	if(len > m_buf.reserve())
	{
		if(m_buf.capacity()*2 <=m_maxlen)
		{
			m_buf.rset_capacity(m_buf.capacity()*2);
			return check_len(len);
		}
		else
		{
			if(m_release > 0)
			{
				//ª∫¥Ê«Â¿Ì
				m_buf.erase(m_buf.begin(), m_buf.begin()+m_release);
				m_release = 0;
				return check_len(len);
			}
			return false;
		}
	}

	return true;
}

uint32_t buffer_base::get_size()
{
	return m_buf.size()- m_release;
}

void buffer_base::clearup()
{
	m_release = 0;
	m_buf.clear();
}

void buffer_base::reset_size(uint32_t blocklen, uint32_t maxlen)
{
	if(m_buf.size() < blocklen)	
		m_buf.set_capacity(blocklen);	

	if( m_maxlen < maxlen)
		m_maxlen = maxlen;
}

//////////////////////////////////////////////////////////////////////////
//send_buffer

send_buffer::send_buffer(uint32_t blocklen, uint32_t maxlen)
	:buffer_base(blocklen, maxlen)
{

}
send_buffer::~send_buffer()
{

}

bool send_buffer::add_data(const char* buf, uint32_t len)
{
	if(!check_len(len)) return false;

	m_buf.insert(m_buf.end(), buf, buf+len);

	return true;
}

bool send_buffer::malloc_buf(uint32_t len)
{
	if(!check_len(len))
		return false;

	static char c = '\0';
	m_buf.insert(m_buf.end(), len, c);

	return true;
}

void send_buffer::release_buf(uint32_t len)
{
	if(len + m_release > m_buf.size())
		return;

	//m_buf.erase(m_buf.begin(), m_buf.begin()+len);
	m_release += len;
}

char* send_buffer::get_sendbuf()
{
	return m_buf.linearize() + m_release;
}

uint32_t send_buffer::get_sendlen()
{
	//if(m_buf.size() > MAX_BUFFER_BLOCK)
	//	return MAX_BUFFER_BLOCK;

	return get_size();
}

//////////////////////////////////////////////////////////////////////////
//recv_buffer

recv_buffer::recv_buffer(uint32_t blocklen, uint32_t maxlen)
	:buffer_base(blocklen, maxlen)
	,m_offset(0)
	,m_left(0)
{

}
recv_buffer::~recv_buffer()
{

}

bool recv_buffer::malloc_buf()
{	
	//if(m_left > MAX_BUFFER_BLOCK/2)
	//	return true;

	int check = MAX_BUFFER_BLOCK-m_left;
	if(check <= 0)
		check = MAX_BUFFER_BLOCK;

	if(!check_len(check))
		return false;

	char c = '\0';
	m_buf.insert(m_buf.end(), check, c);

	m_left+=check;
	
	return true;
}

void recv_buffer::fix_offset(uint32_t len)
{
	m_offset+=len;
	m_left -= len;
}

char* recv_buffer::get_data(char* buf, uint32_t len)
{
	if(len + m_release > m_buf.size())
		return buf;
	
	memcpy(buf, get_head(), len);

	return buf;
}

void recv_buffer::release_buf(uint32_t len)
{
	//m_buf.erase(m_buf.begin(), m_buf.begin()+len);
	m_release += len;
	m_offset -= len;
}

char* recv_buffer::get_head()
{
	return m_buf.linearize()+ m_release;
}

char* recv_buffer::get_recvbuf()
{
	return m_buf.linearize() + m_release + m_offset;
}

uint32_t recv_buffer::get_recvlen()
{
	return get_size() - m_offset;
}

uint32_t recv_buffer::get_offset()
{
	return m_offset;
}
void recv_buffer::clearup()
{
	m_offset = 0;
	m_left = 0;
	buffer_base::clearup();
}