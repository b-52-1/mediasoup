#ifndef MS_RTC_RTCP_FEEDBACK_PS_PLI_HPP
#define MS_RTC_RTCP_FEEDBACK_PS_PLI_HPP

#include "common.hpp"
#include "RTC/RTCP/Feedback.hpp"

namespace RTC
{
	namespace RTCP
	{
		class FeedbackPsPliPacket : public FeedbackPsPacket
		{
		public:
			static FeedbackPsPliPacket* Parse(const uint8_t* data, size_t len);

		public:
			// Parsed Report. Points to an external data.
			explicit FeedbackPsPliPacket(CommonHeader* commonHeader);
			FeedbackPsPliPacket(uint32_t senderSsrc, uint32_t mediaSsrc);
			virtual ~FeedbackPsPliPacket(){};

		public:
			virtual void Dump() const override;
		};

		/* Inline instance methods. */

		inline FeedbackPsPliPacket::FeedbackPsPliPacket(CommonHeader* commonHeader)
		    : FeedbackPsPacket(commonHeader)
		{
		}

		inline FeedbackPsPliPacket::FeedbackPsPliPacket(uint32_t senderSsrc, uint32_t mediaSsrc)
		    : FeedbackPsPacket(FeedbackPs::MessageType::PLI, senderSsrc, mediaSsrc)
		{
		}
	}
}

#endif
