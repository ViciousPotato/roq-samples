/* Copyright (c) 2017-2018, Hans Erik Thrane */

#include "utilities/matcher.h"

#include <roq/logging.h>
#include <roq/stream.h>

#include <limits>

namespace examples {
namespace utilities {

Matcher::Matcher(
    roq::simulation::Matcher::Dispatcher& dispatcher,
    const std::string& name)
    : roq::simulation::Matcher(dispatcher, name) {
  if (name.empty())
    throw std::runtime_error("Gateway name is required");
}

void Matcher::on(const roq::BatchBeginEvent& event) {
}

void Matcher::on(const roq::BatchEndEvent& event) {
}

void Matcher::on(const roq::MarketByPriceEvent& event) {
}

void Matcher::on(const roq::TradeSummaryEvent& event) {
}

void Matcher::on(const roq::CreateOrder& create_order) {
  auto create_order_ack = roq::CreateOrderAck {
    .account = create_order.account,
    .order_id = create_order.order_id,
    .failure = false,
    .reason = "",
    .order_local_id = 0,
    .order_external_id = "",
  };
  send(create_order_ack);
  auto order_update = roq::OrderUpdate {
    .account = create_order.account,
    .order_id = create_order.order_id,
    .exchange = create_order.exchange,
    .symbol = create_order.symbol,
    .order_status = roq::OrderStatus::Completed,
    .side = create_order.side,
    .remaining_quantity = 0.0,
    .traded_quantity = create_order.quantity,
    .position_effect = create_order.position_effect,
    .order_template = create_order.order_template,
    .insert_time = std::chrono::time_point_cast<roq::duration_t>(
        std::chrono::system_clock::time_point()),
    .cancel_time = std::chrono::time_point_cast<roq::duration_t>(
        std::chrono::system_clock::time_point()),
    .order_local_id = 0,
    .order_external_id = "",
  };
  send(order_update);
  auto trade_update = roq::TradeUpdate {
    .account = create_order.account,
    .trade_id = create_order.order_id,
    .order_id = create_order.order_id,
    .exchange = create_order.exchange,
    .symbol = create_order.symbol,
    .side = create_order.side,
    .quantity = 0.0,
    .price = create_order.limit_price,
    .position_effect = create_order.position_effect,
    .order_template = create_order.order_template,
    .trade_time = std::chrono::time_point_cast<roq::duration_t>(
        std::chrono::system_clock::time_point()),
    .order_external_id = "",
    .trade_external_id = "",
  };
  send(trade_update);
}

void Matcher::on(const roq::ModifyOrder& modify_order) {
  auto modify_order_ack = roq::ModifyOrderAck {
    .account = modify_order.account,
    .order_id = modify_order.order_id,
    .failure = true,
    .reason = "NOT_SUPPORTED",
    .order_local_id = 0,
    .order_external_id = "",
  };
  send(modify_order_ack);
}

void Matcher::on(const roq::CancelOrder& cancel_order) {
  auto cancel_order_ack = roq::CancelOrderAck {
    .account = cancel_order.account,
    .order_id = cancel_order.order_id,
    .failure = true,
    .reason = "NOT_SUPPORTED",
    .order_local_id = 0,
    .order_external_id = "",
  };
  send(cancel_order_ack);
}

}  // namespace utilities
}  // namespace examples
