/*
 * Code generator for Equid project
 * (C) Maxim Menshikov 2019-2020
 */
#pragma once
#include <string>

class MemberData
{
public:
    MemberData() = default;
    virtual ~MemberData() = default;
    MemberData(const MemberData &rhs) = default;
    MemberData &operator=(const MemberData &rhs) = default;

    /**
     * @brief      Set the read only mode property
     *
     * @param      ro    The new value, @c true to enable, @c false to disable
     */
    void setIsReadOnly(bool ro);
    /**
     * @brief      Get the read only mode property
     *
     * @return     The read only property
     */
    bool isReadOnly() const;

    /**
     * @brief      Set the purity of the member (in sense that it should be
     *             overriden by subclasses)
     *
     * @param      pur   The new value, @c true to enable, @c false to disable
     */
    void setIsPure(bool pur);
    /**
     * @brief      Get the purity of the member (in sense that it should be
     *             overriden by subclasses)
     *
     * @return     The purity of the member
     */
    bool isPure() const;


    /**
     * @brief      Set the type of the member
     *
     * @param      type  The type
     */
    void setType(std::string type);
    /**
     * @brief      Get the type of the member
     *
     * @return     The type.
     */
    std::string getType() const;

    /**
     * @brief      Set the public name of the member
     *
     * @param[in]  name  The name
     */
    void setName(std::string name);
    /**
     * @brief      Get the public name of the member
     *
     * @return     The name.
     */
    std::string getName() const;

    /**
     * @brief      Set the internal name of the member
     *
     * @param      name  The name
     */
    void setMemberName(std::string name);
    /**
     * @brief      Get the internal name of the member
     *
     * @return     The name.
     */
    std::string getMemberName() const;

private:
    bool        _isReadOnly;
    bool        _isPure;
    std::string _type;
    std::string _name;
    std::string _memberName;
};