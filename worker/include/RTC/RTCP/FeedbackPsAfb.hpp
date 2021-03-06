#ifndef MS_RTC_RTCP_FEEDBACK_PS_AFB_HPP
#define MS_RTC_RTCP_FEEDBACK_PS_AFB_HPP

#include "common.hpp"
#include "RTC/RTCP/Feedback.hpp"

namespace RTC
{
	namespace RTCP
	{
		class FeedbackPsAfbPacket : public FeedbackPsPacket
		{
		public:
			typedef enum Application : uint8_t { UNKNOWN = 0, REMB = 1 } Application;

		public:
			static FeedbackPsAfbPacket* Parse(const uint8_t* data, size_t len);

		public:
			// Parsed Report. Points to an external data.
			explicit FeedbackPsAfbPacket(CommonHeader* commonHeader, Application application = UNKNOWN);
			FeedbackPsAfbPacket(uint32_t senderSsrc, uint32_t mediaSsrc, Application application = UNKNOWN);
			virtual ~FeedbackPsAfbPacket(){};

			Application GetApplication() const;

			/* Pure virtual methods inherited from Packet. */
		public:
			virtual void Dump() const override;
			virtual size_t Serialize(uint8_t* buffer) override;
			virtual size_t GetSize() const override;

		private:
			Application application = UNKNOWN;
			uint8_t* data           = nullptr;
			size_t size             = 0;
		};

		/* Inline instance methods. */

		inline FeedbackPsAfbPacket::FeedbackPsAfbPacket(CommonHeader* commonHeader, Application application)
		    : FeedbackPsPacket(commonHeader)
		{
			this->size = ((ntohs(commonHeader->length) + 1) * 4) -
			             (sizeof(CommonHeader) + sizeof(FeedbackPacket::Header));

			this->data = (uint8_t*)commonHeader + sizeof(CommonHeader) + sizeof(FeedbackPacket::Header);

			this->application = application;
		}

		inline FeedbackPsAfbPacket::FeedbackPsAfbPacket(
		    uint32_t senderSsrc, uint32_t mediaSsrc, Application application)
		    : FeedbackPsPacket(FeedbackPs::MessageType::AFB, senderSsrc, mediaSsrc)
		{
			this->application = application;
		}

		inline FeedbackPsAfbPacket::Application FeedbackPsAfbPacket::GetApplication() const
		{
			return this->application;
		}

		inline size_t FeedbackPsAfbPacket::GetSize() const
		{
			return FeedbackPsPacket::GetSize() + this->size;
		}
	}
}

#endif
