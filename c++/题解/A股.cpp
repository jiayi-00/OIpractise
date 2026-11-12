#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <numeric>
#include <memory>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <queue>

// ==================== 核心数据结构 ====================
namespace quant {
    
struct OHLCV {
    double open = 0.0;
    double high = 0.0;
    double low = 0.0
    double close = 0.0;
    long long volume = 0;
    double amount = 0.0;
    
    bool valid() const { return close > 1e-9 && volume > 0; }
};

struct DailyData {
    std::string date;
    std::string symbol;
    OHLCV ohlcv;
    double amplitude = 0.0;
    double pct_change = 0.0;
    double change = 0.0;
    double turnover = 0.0;
    
    bool suspended() const { return ohlcv.open < 1e-9 || ohlcv.volume == 0; }
    bool limit_up() const { return pct_change >= 9.8; }
    bool limit_down() const { return pct_change <= -9.8; }
};

// ==================== 技术指标模块 ====================
namespace indicators {
    
class MovingAverage {
private:
    int period_;
    
public:
    explicit MovingAverage(int period) : period_(period) {}
    
    double calculate(const std::vector<double>& prices) const {
        if (prices.size() < static_cast<size_t>(period_)) return 0.0;
        double sum = 0.0;
        for (size_t i = prices.size() - period_; i < prices.size(); ++i) {
            sum += prices[i];
        }
        return sum / period_;
    }
};

class RSI {
private:
    int period_;
    
public:
    explicit RSI(int period = 14) : period_(period) {}
    
    double calculate(const std::vector<double>& prices) const {
        if (prices.size() < static_cast<size_t>(period_ + 1)) return 50.0;
        
        double total_gain = 0.0, total_loss = 0.0;
        for (size_t i = prices.size() - period_; i < prices.size(); ++i) {
            double change = prices[i] - prices[i - 1];
            if (change > 0) {
                total_gain += change;
            } else {
                total_loss -= change;
            }
        }
        
        double avg_gain = total_gain / period_;
        double avg_loss = total_loss / period_;
        
        if (avg_loss < 1e-9) return 100.0;
        double rs = avg_gain / avg_loss;
        return 100.0 - (100.0 / (1.0 + rs));
    }
};

// 动量计算
double momentum(const std::vector<double>& prices, int period = 20) {
    if (prices.size() < static_cast<size_t>(period)) return 0.0;
    double current = prices.back();
    double past = prices[prices.size() - period];
    return (current - past) / past;
}

// 波动率计算
double volatility(const std::vector<double>& prices, int period = 20) {
    if (prices.size() < static_cast<size_t>(period)) return 0.0;
    
    std::vector<double> returns;
    for (size_t i = prices.size() - period + 1; i < prices.size(); ++i) {
        double ret = (prices[i] - prices[i - 1]) / prices[i - 1];
        returns.push_back(ret);
    }
    
    double mean = 0.0;
    for (double ret : returns) {
        mean += ret;
    }
    mean /= returns.size();
    
    double variance = 0.0;
    for (double ret : returns) {
        variance += (ret - mean) * (ret - mean);
    }
    variance /= (returns.size() - 1);
    
    return std::sqrt(variance);
}

} // namespace indicators

// ==================== 因子计算模块 ====================
namespace factors {
    
struct FactorScores {
    double momentum = 0.0;
    double value = 0.0;
    double quality = 0.0;
    double growth = 0.0;
    double technical = 0.0;
    double sentiment = 0.0;
    
    double total() const {
        return 0.3 * momentum + 0.2 * value + 0.15 * quality + 
               0.15 * growth + 0.15 * technical + 0.05 * sentiment;
    }
};

class FactorCalculator {
public:
    FactorScores calculate(const DailyData& current,
                          const std::vector<DailyData>& history) const {
        FactorScores scores;
        
        // 提取收盘价序列
        std::vector<double> closes;
        for (size_t i = 0; i < history.size(); ++i) {
            closes.push_back(history[i].ohlcv.close);
        }
        
        // 动量因子
        scores.momentum = indicators::momentum(closes, 20);
        
        // 技术因子（RSI）
        indicators::RSI rsi(14);
        double rsi_value = rsi.calculate(closes);
        scores.technical = (rsi_value - 50.0) / 50.0;
        
        // 质量因子（波动率倒数）
        double vol = indicators::volatility(closes, 20);
        scores.quality = vol > 0 ? 1.0 / (1.0 + vol) : 0.0;
        
        // 情绪因子（量价关系）
        if (current.ohlcv.volume > 0) {
            double vwap = current.ohlcv.amount / current.ohlcv.volume;
            scores.sentiment = (current.ohlcv.close - vwap) / vwap;
        }
        
        return scores;
    }
};

} // namespace factors

// ==================== 账户管理模块 ====================
class Portfolio {
public:
    struct Holding {
        std::string symbol;
        long long shares = 0;
        double avg_cost = 0.0;
        double market_value = 0.0;
        double pnl = 0.0;
        double pnl_pct = 0.0;
        int entry_day = 0;
        
        void update(double current_price) {
            market_value = shares * current_price;
            if (avg_cost > 1e-9) {
                pnl = (current_price - avg_cost) * shares;
                pnl_pct = (current_price - avg_cost) / avg_cost;
            }
        }
    };
    
private:
    double cash_ = 100000.0;
    double total_equity_ = 100000.0;
    double peak_equity_ = 100000.0;
    double max_drawdown_ = 0.0;
    
    std::unordered_map<std::string, Holding> holdings_;
    std::vector<double> equity_curve_;
    
public:
    Portfolio(double initial_capital = 100000.0) 
        : cash_(initial_capital), total_equity_(initial_capital), 
          peak_equity_(initial_capital) {}
    
    bool can_buy(const std::string& symbol, long long shares, double price, 
                 double commission) const {
        double cost = price * shares + commission;
        return cash_ >= cost;
    }
    
    bool can_sell(const std::string& symbol, long long shares) const {
        auto it = holdings_.find(symbol);
        return it != holdings_.end() && it->second.shares >= shares;
    }
    
    void update_holdings(const std::unordered_map<std::string, double>& prices) {
        total_equity_ = cash_;
        
        for (auto it = holdings_.begin(); it != holdings_.end(); ++it) {
            const std::string& symbol = it->first;
            Holding& holding = it->second;
            
            auto price_it = prices.find(symbol);
            if (price_it != prices.end()) {
                holding.update(price_it->second);
                total_equity_ += holding.market_value;
            }
        }
        
        // 计算最大回撤
        if (total_equity_ > peak_equity_) {
            peak_equity_ = total_equity_;
        }
        double drawdown = (peak_equity_ - total_equity_) / peak_equity_;
        if (drawdown > max_drawdown_) {
            max_drawdown_ = drawdown;
        }
        
        equity_curve_.push_back(total_equity_);
    }
    
    double cash() const { return cash_; }
    double total_equity() const { return total_equity_; }
    double max_drawdown() const { return max_drawdown_; }
    size_t position_count() const { return holdings_.size(); }
    
    void add_holding(const std::string& symbol, long long shares, 
                    double price, int current_day) {
        auto it = holdings_.find(symbol);
        if (it == holdings_.end()) {
            Holding holding;
            holding.symbol = symbol;
            holding.shares = shares;
            holding.avg_cost = price;
            holding.entry_day = current_day;
            holdings_[symbol] = holding;
        } else {
            Holding& holding = it->second;
            double total_cost = holding.avg_cost * holding.shares + price * shares;
            holding.shares += shares;
            holding.avg_cost = total_cost / holding.shares;
        }
        cash_ -= price * shares;
    }
    
    void remove_holding(const std::string& symbol, long long shares, double price) {
        auto it = holdings_.find(symbol);
        if (it != holdings_.end()) {
            it->second.shares -= shares;
            cash_ += price * shares;
            if (it->second.shares == 0) {
                holdings_.erase(it);
            }
        }
    }
    
    const Holding* get_holding(const std::string& symbol) const {
        auto it = holdings_.find(symbol);
        return it != holdings_.end() ? &it->second : nullptr;
    }
    
    // 获取所有持仓的迭代器
    std::unordered_map<std::string, Holding>::const_iterator holdings_begin() const {
        return holdings_.begin();
    }
    
    std::unordered_map<std::string, Holding>::const_iterator holdings_end() const {
        return holdings_.end();
    }
};

// ==================== 交易策略接口 ====================
class TradingStrategy {
public:
    virtual ~TradingStrategy() {}
    
    struct Signal {
        std::string symbol;
        long long quantity;  // 使用long long避免类型转换警告
        double confidence;
        std::string reason;
        
        Signal(const std::string& sym, long long qty, double conf, const std::string& rsn)
            : symbol(sym), quantity(qty), confidence(conf), reason(rsn) {}
    };
    
    virtual std::vector<Signal> generate_signals(
        const std::unordered_map<std::string, DailyData>& market_data,
        const Portfolio& portfolio,
        int current_day) = 0;
    
    virtual void update_market_state(
        const std::unordered_map<std::string, DailyData>& market_data) = 0;
    
    virtual std::string strategy_name() const = 0;
};

// ==================== 动量反转策略 ====================
class MomentumReversalStrategy : public TradingStrategy {
private:
    struct Parameters {
        int lookback_days = 5;
        int min_holding_days = 3;
        int max_holding_days = 10;
        double stop_loss = -0.08;
        double take_profit = 0.15;
        double max_position_pct = 0.10;
        int max_positions = 12;
        double min_price = 5.0;
        double min_turnover = 0.5;
    } params_;
    
    std::unordered_map<std::string, int> entry_days_;
    std::unordered_map<std::string, double> entry_prices_;
    std::string market_state_ = "NORMAL";
    
public:
    MomentumReversalStrategy() {}
    
    std::vector<Signal> generate_signals(
        const std::unordered_map<std::string, DailyData>& market_data,
        const Portfolio& portfolio,
        int current_day) override {
        
        std::vector<Signal> signals;
        
        // 1. 卖出逻辑
        process_sell_signals(market_data, portfolio, current_day, signals);
        
        // 2. 买入逻辑
        if (portfolio.position_count() < static_cast<size_t>(params_.max_positions)) {
            process_buy_signals(market_data, portfolio, current_day, signals);
        }
        
        return signals;
    }
    
    void update_market_state(
        const std::unordered_map<std::string, DailyData>& market_data) override {
        
        int up_count = 0, total = 0;
        double total_change = 0.0;
        
        for (auto it = market_data.begin(); it != market_data.end(); ++it) {
            const DailyData& data = it->second;
            if (!data.suspended()) {
                total_change += data.pct_change;
                if (data.pct_change > 0) up_count++;
                total++;
            }
        }
        
        if (total == 0) {
            market_state_ = "UNKNOWN";
            return;
        }
        
        double up_ratio = static_cast<double>(up_count) / total;
        double avg_change = total_change / total;
        
        if (avg_change > 1.5 && up_ratio > 0.7) {
            market_state_ = "STRONG_BULL";
            params_.take_profit = 0.20;
            params_.stop_loss = -0.10;
        } else if (avg_change > 0.8 && up_ratio > 0.6) {
            market_state_ = "BULL";
            params_.take_profit = 0.15;
            params_.stop_loss = -0.08;
        } else if (avg_change < -1.5 && up_ratio < 0.3) {
            market_state_ = "STRONG_BEAR";
            params_.take_profit = 0.10;
            params_.stop_loss = -0.05;
            params_.max_positions = 6;
        } else if (avg_change < -0.8 && up_ratio < 0.4) {
            market_state_ = "BEAR";
            params_.take_profit = 0.12;
            params_.stop_loss = -0.06;
            params_.max_positions = 8;
        } else {
            market_state_ = "SIDEWAYS";
            params_.take_profit = 0.12;
            params_.stop_loss = -0.07;
            params_.max_positions = 10;
        }
    }
    
    std::string strategy_name() const override { 
        return "MomentumReversalStrategy"; 
    }
    
private:
    void process_sell_signals(
        const std::unordered_map<std::string, DailyData>& market_data,
        const Portfolio& portfolio,
        int current_day,
        std::vector<Signal>& signals) {
        
        auto it_begin = portfolio.holdings_begin();
        auto it_end = portfolio.holdings_end();
        
        for (auto it = it_begin; it != it_end; ++it) {
            const std::string& symbol = it->first;
            const Portfolio::Holding& holding = it->second;
            
            auto data_it = market_data.find(symbol);
            if (data_it == market_data.end()) continue;
            
            const DailyData& data = data_it->second;
            const Portfolio::Holding* pos = portfolio.get_holding(symbol);
            if (!pos) continue;
            
            // 止损止盈检查
            if (pos->pnl_pct <= params_.stop_loss || 
                pos->pnl_pct >= params_.take_profit) {
                signals.push_back(Signal(symbol, -pos->shares, 1.0, 
                    pos->pnl_pct <= params_.stop_loss ? "止损" : "止盈"));
                entry_days_.erase(symbol);
                entry_prices_.erase(symbol);
                continue;
            }
            
            // 持有时间检查
            auto entry_it = entry_days_.find(symbol);
            if (entry_it != entry_days_.end()) {
                int holding_days = current_day - entry_it->second;
                if (holding_days >= params_.max_holding_days) {
                    signals.push_back(Signal(symbol, -pos->shares, 0.8, "持有到期"));
                    entry_days_.erase(symbol);
                    entry_prices_.erase(symbol);
                }
            }
            
            // 停牌或跌停
            if (data.suspended() || data.limit_down()) {
                signals.push_back(Signal(symbol, -pos->shares, 1.0, "停牌/跌停"));
                entry_days_.erase(symbol);
                entry_prices_.erase(symbol);
            }
        }
    }
    
    void process_buy_signals(
        const std::unordered_map<std::string, DailyData>& market_data,
        const Portfolio& portfolio,
        int current_day,
        std::vector<Signal>& signals) {
        
        std::vector<std::pair<std::string, double>> candidates;
        
        for (auto it = market_data.begin(); it != market_data.end(); ++it) {
            const std::string& symbol = it->first;
            const DailyData& data = it->second;
            
            if (should_filter_stock(data)) continue;
            if (portfolio.get_holding(symbol)) continue;
            
            double score = calculate_stock_score(data, market_data);
            if (score > 0) {
                candidates.push_back(std::make_pair(symbol, score));
            }
        }
        
        // 按分数排序
        std::sort(candidates.begin(), candidates.end(),
                  [](const std::pair<std::string, double>& a, 
                     const std::pair<std::string, double>& b) {
                      return a.second > b.second;
                  });
        
        // 选择前N名
        int available_slots = params_.max_positions - portfolio.position_count();
        int buy_count = std::min(static_cast<int>(candidates.size()), available_slots);
        
        for (int i = 0; i < buy_count; i++) {
            const std::string& symbol = candidates[i].first;
            double score = candidates[i].second;
            
            const DailyData& data = market_data.at(symbol);
            
            // 计算买入数量
            long long shares = calculate_position_size(data.ohlcv.close, 
                                                      portfolio.total_equity(),
                                                      score);
            
            if (shares > 0) {
                signals.push_back(Signal(symbol, shares, score / 10.0, "动量买入"));
                entry_days_[symbol] = current_day;
                entry_prices_[symbol] = data.ohlcv.close;
            }
        }
    }
    
    bool should_filter_stock(const DailyData& data) const {
        return data.suspended() || 
               data.limit_up() ||
               data.ohlcv.close < params_.min_price ||
               data.turnover < params_.min_turnover ||
               data.ohlcv.volume < 1000000;
    }
    
    double calculate_stock_score(const DailyData& data,
                                const std::unordered_map<std::string, DailyData>& market_data) const {
        double score = 0.0;
        
        // 动量得分
        if (data.pct_change > 0) {
            score += std::min(data.pct_change, 10.0) / 10.0 * 4.0;
        }
        
        // 成交量得分
        if (data.turnover > 3.0) {
            score += 2.0;
        } else if (data.turnover > 1.5) {
            score += 1.0;
        }
        
        // 价格位置得分
        if (data.ohlcv.close > data.ohlcv.open) {
            score += 2.0;
        }
        
        // 振幅得分
        if (data.amplitude > 2.0 && data.amplitude < 8.0) {
            score += 1.0;
        }
        
        return score;
    }
    
    long long calculate_position_size(double price, double total_equity, double score) const {
        double position_value = total_equity * params_.max_position_pct * (score / 10.0);
        long long shares = static_cast<long long>(position_value / price / 100) * 100;
        return std::max(shares, 100LL);
    }
};

// ==================== 交易引擎配置 ====================
struct TradingConfig {
    double initial_capital = 100000.0;
    int lot_size = 100;
    double commission_rate = 0.0003;
    double min_commission = 5.0;
    double stamp_tax = 0.001;
    int max_orders_per_day = 500;
    
    TradingConfig() = default;
    
    TradingConfig(double capital, int lot, double comm_rate, double min_comm,
                  double tax, int max_orders)
        : initial_capital(capital), lot_size(lot), commission_rate(comm_rate),
          min_commission(min_comm), stamp_tax(tax), max_orders_per_day(max_orders) {}
};

// ==================== 交易引擎 ====================
class TradingEngine {
private:
    std::unique_ptr<TradingStrategy> strategy_;
    Portfolio portfolio_;
    TradingConfig config_;
    int current_day_ = 0;
    
    std::unordered_map<std::string, std::vector<DailyData>> historical_data_;
    
public:
    TradingEngine(std::unique_ptr<TradingStrategy> strategy, const TradingConfig& config)
        : strategy_(std::move(strategy)), config_(config), 
          portfolio_(config.initial_capital) {}
    
    std::vector<std::string> process_daily_data(
        const std::vector<DailyData>& daily_data) {
        
        current_day_++;
        
        // 1. 更新市场数据
        update_market_data(daily_data);
        
        // 2. 构建当前市场数据映射
        std::unordered_map<std::string, DailyData> current_map;
        for (size_t i = 0; i < daily_data.size(); ++i) {
            current_map[daily_data[i].symbol] = daily_data[i];
        }
        
        // 3. 更新策略市场状态
        strategy_->update_market_state(current_map);
        
        // 4. 生成交易信号
        auto signals = strategy_->generate_signals(current_map, portfolio_, current_day_);
        
        // 5. 转换为订单
        std::vector<std::string> orders;
        convert_signals_to_orders(signals, current_map, orders);
        
        // 6. 更新持仓市值
        update_portfolio_values(current_map);
        
        return orders;
    }
    
    const Portfolio& portfolio() const { return portfolio_; }
    int current_day() const { return current_day_; }
    
private:
    void update_market_data(const std::vector<DailyData>& daily_data) {
        for (size_t i = 0; i < daily_data.size(); ++i) {
            const DailyData& data = daily_data[i];
            historical_data_[data.symbol].push_back(data);
            
            // 保持最近100个交易日数据
            if (historical_data_[data.symbol].size() > 100) {
                historical_data_[data.symbol].erase(
                    historical_data_[data.symbol].begin());
            }
        }
    }
    
    void convert_signals_to_orders(
        const std::vector<TradingStrategy::Signal>& signals,
        const std::unordered_map<std::string, DailyData>& market_data,
        std::vector<std::string>& orders) {
        
        int order_count = 0;
        
        for (size_t i = 0; i < signals.size(); ++i) {
            if (order_count >= config_.max_orders_per_day) break;
            
            const TradingStrategy::Signal& signal = signals[i];
            auto data_it = market_data.find(signal.symbol);
            if (data_it == market_data.end()) continue;
            
            const DailyData& data = data_it->second;
            double price = data.ohlcv.open; // 使用开盘价执行
            
            if (signal.quantity > 0) { // 买入
                double cost = price * signal.quantity;
                double commission = std::max(config_.min_commission, 
                                           cost * config_.commission_rate);
                commission = std::round(commission * 100) / 100;
                
                if (portfolio_.can_buy(signal.symbol, signal.quantity, price, commission)) {
                    portfolio_.add_holding(signal.symbol, signal.quantity, 
                                         price, current_day_);
                    
                    std::ostringstream oss;
                    oss << "BUY " << signal.symbol << " " << signal.quantity;
                    orders.push_back(oss.str());
                    order_count++;
                }
            } else { // 卖出
                long long sell_shares = -signal.quantity;
                
                if (portfolio_.can_sell(signal.symbol, sell_shares)) {
                    double revenue = price * sell_shares;
                    double tax = revenue * config_.stamp_tax;
                    double commission = std::max(config_.min_commission, 
                                               revenue * config_.commission_rate);
                    
                    tax = std::round(tax * 100) / 100;
                    commission = std::round(commission * 100) / 100;
                    
                    portfolio_.remove_holding(signal.symbol, sell_shares, price);
                    
                    std::ostringstream oss;
                    oss << "SELL " << signal.symbol << " " << sell_shares;
                    orders.push_back(oss.str());
                    order_count++;
                }
            }
        }
    }
    
    void update_portfolio_values(
        const std::unordered_map<std::string, DailyData>& market_data) {
        
        std::unordered_map<std::string, double> prices;
        for (auto it = market_data.begin(); it != market_data.end(); ++it) {
            const std::string& symbol = it->first;
            const DailyData& data = it->second;
            prices[symbol] = data.ohlcv.close;
        }
        
        portfolio_.update_holdings(prices);
    }
};

// ==================== 数据解析器 ====================
class DataParser {
public:
    static DailyData parse_line(const std::string& line) {
        DailyData data;
        std::vector<std::string> tokens;
        
        if (line.find(',') != std::string::npos) {
            std::stringstream ss(line);
            std::string token;
            while (std::getline(ss, token, ',')) {
                tokens.push_back(token);
            }
        } else {
            std::stringstream ss(line);
            std::string token;
            while (ss >> token) {
                tokens.push_back(token);
            }
        }
        
        if (tokens.size() >= 12) {
            data.date = tokens[0];
            data.symbol = tokens[1];
            data.ohlcv.open = std::stod(tokens[2]);
            data.ohlcv.high = std::stod(tokens[3]);
            data.ohlcv.low = std::stod(tokens[4]);
            data.ohlcv.close = std::stod(tokens[5]);
            data.ohlcv.volume = std::stoll(tokens[6]);
            data.ohlcv.amount = std::stod(tokens[7]);
            data.amplitude = std::stod(tokens[8]);
            data.pct_change = std::stod(tokens[9]);
            data.change = std::stod(tokens[10]);
            data.turnover = std::stod(tokens[11]);
        }
        
        return data;
    }
};

} // namespace quant

// ==================== 主程序 ====================
int main() {
    using namespace quant;
    
    // 提高IO性能
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << std::fixed << std::setprecision(2);
    
    try {
        // 1. 读取初始化参数
        std::string init_line;
        std::getline(std::cin, init_line);
        
        std::stringstream ss(init_line);
        std::string cmd;
        int n, D, L, K_max;
        double m, alpha, com_min, beta;
        
        ss >> cmd >> n >> D >> m >> L >> alpha >> com_min >> beta >> K_max;
        
        // 2. 配置交易引擎
        TradingConfig config(m, L, alpha, com_min, beta, K_max);
        
        auto strategy = std::unique_ptr<TradingStrategy>(new MomentumReversalStrategy());
        TradingEngine engine(std::move(strategy), config);
        
        // 3. 读取初始数据（day 0）
        std::vector<DailyData> day0_data;
        for (int i = 0; i < n; ++i) {
            std::string line;
            std::getline(std::cin, line);
            day0_data.push_back(DataParser::parse_line(line));
        }
        
        // 4. 处理初始数据并生成第一天订单
        auto orders = engine.process_daily_data(day0_data);
        for (size_t i = 0; i < orders.size(); ++i) {
            std::cout << orders[i] << "\n";
        }
        std::cout << "DONE\n";
        std::cout.flush();
        
        // 5. 主交易循环
        for (int day = 1; day <= D; ++day) {
            // 读取当日数据
            std::vector<DailyData> daily_data;
            for (int i = 0; i < n; ++i) {
                std::string line;
                std::getline(std::cin, line);
                
                if (line.find("FINISH") == 0) {
                    // 输出最终资产
                    const Portfolio& portfolio = engine.portfolio();
                    std::cout << "FINISH " << portfolio.total_equity() << "\n";
                    return 0;
                }
                
                daily_data.push_back(DataParser::parse_line(line));
            }
            
            // 处理数据并生成订单
            orders = engine.process_daily_data(daily_data);
            for (size_t i = 0; i < orders.size(); ++i) {
                std::cout << orders[i] << "\n";
            }
            std::cout << "DONE\n";
            std::cout.flush();
        }
        
        // 6. 读取最终结果
        std::string final_line;
        std::getline(std::cin, final_line);
        
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
        std::cout << "DONE\n";
        std::cout.flush();
        return 1;
    }
    
    return 0;
}
