#include "Code.hpp"

namespace Sem
{

IdentExpr::IdentExpr(const std::string& ident): ident(ident) {}

QName::QName(const IdentExpr* part) {
	this->_parts.push_back(part);
}

QName::QName(const QName::ListType& parts)
	: _parts(parts) {}

QName QName::append(const IdentExpr* part) const {
	QName newobj(this->_parts);
	newobj._parts.push_back(part);
	return newobj;
}

const IdentExpr* QName::last() const {
	return this->_parts.back();
}

const IdentExpr* QName::first() const {
	return this->_parts.front();
}

const QName::ListType& QName::parts() const {
	return this->_parts;
}

}
