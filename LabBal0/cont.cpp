bool isCont(vector<Cont> cont, int vsize, int i)
{
    if (i >= vsize || cont[i].is_end) {
        return false;
    }
    return true;
}
void pushCont(vector<Cont>& cont, int num)
{
    Cont temp = {num, 0, true, false};
    cont.push_back(temp);
}
void endCont(vector<Cont>& cont)
{
    for (int i = 0; i < cont.size(); i++) {
        if (!cont[i].isset) {
            cont[i].is_end = true;
            break;
        }
    }
}